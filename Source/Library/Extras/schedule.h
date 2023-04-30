//
// schedule.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2012-2014 Michael F. Henry
// Version 08/2014
//
#pragma once
#include "stdafx.h"

#include "cOrbit.h"
#include "utility.h"
#include <stack>
#include <memory>
#include <sstream>
#include <vector>
#include <iterator>
#include <time.h>

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{
   /// <summary>
   /// Class to abstract a time period with start, stop times and arbitrary
   /// content associated with the time period.
   /// </summary>
   template <typename T> class cPeriodInfo
   {
   public:
      cPeriodInfo(cJulian start, cJulian stop);
      cPeriodInfo(cJulian start, cJulian stop, const shared_ptr<T>& content);
      cPeriodInfo(cJulian start, cJulian stop, const vector<shared_ptr<T>>& contents);
      cPeriodInfo(cJulian start, cJulian stop, int overlapCount, const cPeriodInfo<T>& content);

      void AddContent(const vector<shared_ptr<T>>& items);
      void AddContent(const shared_ptr<T>& item);

      int OverlapCount() const;
      vector<shared_ptr<T>> Content() const;
      bool Overlaps(const shared_ptr<cPeriodInfo<T>>& p) const;
      string ToString() const;
      
      static int Start_LT       (const shared_ptr<cPeriodInfo<T>>& x, const shared_ptr<cPeriodInfo<T>>& y);
      static int OverlapCount_LT(const shared_ptr<cPeriodInfo<T>>& x, const shared_ptr<cPeriodInfo<T>>& y);
      static int OverlapCount_GT(const shared_ptr<cPeriodInfo<T>>& x, const shared_ptr<cPeriodInfo<T>>& y);

      cJulian Start() const { return m_start; }
      cJulian Stop()  const { return m_stop;  }

   private:
      void CommonConstruct(cJulian start, cJulian stop);

      cJulian m_start;
      cJulian m_stop;
      int m_overlapCount;
      vector<shared_ptr<T>> m_content;
   };

   /// <summary>
   /// Class to abstract a collection of time periods, where each period may
   /// have associated with it arbitrary content.
   /// </summary>
   template <typename T> class cSchedule
   {
   public:
      cSchedule();
      cSchedule(const vector<shared_ptr<cPeriodInfo<T>>>& periods);
      virtual ~cSchedule();

      vector<shared_ptr<cPeriodInfo<T>>> SortOverlapCount()     const;
      vector<shared_ptr<cPeriodInfo<T>>> SortOverlapCountDesc() const;
      vector<shared_ptr<cPeriodInfo<T>>> OverlapMax() const;
      vector<shared_ptr<cPeriodInfo<T>>> OverlapMin() const;

      vector<shared_ptr<cPeriodInfo<T>>> Periods() const;
      vector<shared_ptr<cPeriodInfo<T>>> Periods(int minOverlap, int maxOverlap) const;

      void AddPeriod(cJulian start, cJulian stop, const vector<shared_ptr<T>>* content = nullptr);
      void AddPeriod(const shared_ptr<cPeriodInfo<T>>& period);
      void AddPeriod(const vector<shared_ptr<cPeriodInfo<T>>>& periods);

      string ToString() const;

   private:
      void CommonConstruct();

      void Process        (const shared_ptr<cPeriodInfo<T>>& a, const shared_ptr<cPeriodInfo<T>>& b);
      void ProcessOverlap (const shared_ptr<cPeriodInfo<T>>& a, const shared_ptr<cPeriodInfo<T>>& b);
      void ProcessDisjoint(const shared_ptr<cPeriodInfo<T>>& a, const shared_ptr<cPeriodInfo<T>>& b);
      void ProcessSingle  (const shared_ptr<cPeriodInfo<T>>& a);

      int CalcMinOverlapCount() const;

      deque<shared_ptr<cPeriodInfo<T>>> m_sortedPeriods;
      vector<shared_ptr<cPeriodInfo<T>>> m_processed;
      stack <shared_ptr<cPeriodInfo<T>>> m_stack;
      cJulian m_minTime;
      cJulian m_maxTime;
      int m_maxOverlapCount;
   };

#pragma region Schedule

#pragma region Construction

   /// <summary>
   /// Standard constructor.
   /// </summary>
   template<typename T> cSchedule<T>::cSchedule()
   {
      CommonConstruct();
   }

   /// <summary>
   /// Constructor accepting vector of periods.
   /// </summary>
   template<typename T> 
   cSchedule<T>::cSchedule(const vector<shared_ptr<cPeriodInfo<T>>>& periods)
   {
      for (auto ptr = periods.cbegin(); ptr != periods.cend(); ptr++)
      {
         AddPeriod(*ptr);
      }

      CommonConstruct();
   }
      
   // Private construction helper
   template<typename T>
   void cSchedule<T>::CommonConstruct()
   {
      // Set to arbitrary "maximum" and "minimum" Julian dates
      this->m_minTime = cJulian(1583, 1);
      this->m_maxTime = cJulian(2999, 1);

      m_maxOverlapCount = 0;
   }

   /// <summary>
   /// Standard destructor.
   /// </summary>
   template<typename T> 
   cSchedule<T>::~cSchedule()
   {
      m_sortedPeriods.clear();
      m_processed.clear();
   }

#pragma endregion

#pragma region Properties
   
   /// <summary>
   /// Returns the collection of time periods, sorted by ascending overlap count.
   /// </summary>
   template<typename T>
   vector<shared_ptr<cPeriodInfo<T>>> cSchedule<T>::SortOverlapCount() const
   {
      vector<shared_ptr<cPeriodInfo<T>>> periods;
      
      periods.reserve(m_sortedPeriods.size());
      copy(m_sortedPeriods.begin(), m_sortedPeriods.end(), back_inserter(periods));
      stable_sort(periods.begin(), periods.end(), cPeriodInfo<T>::OverlapCount_LT);

      return periods;
   }
   
   /// <summary>
   /// Returns the collection of time periods, sorted by descending overlap count.
   /// </summary>
   template<typename T>
   vector<shared_ptr<cPeriodInfo<T>>> cSchedule<T>::SortOverlapCountDesc() const
   {
      vector<shared_ptr<cPeriodInfo<T>>> periods;

      periods.reserve(m_sortedPeriods.size());
      copy(m_sortedPeriods.begin(), m_sortedPeriods.end(), back_inserter(periods));
      stable_sort(periods.begin(), periods.end(), cPeriodInfo<T>::OverlapCount_GT);

      return periods;
   }
   
   /// <summary>
   /// Returns the collection of time periods that have the highest overlap count.
   /// </summary>
   template<typename T>
   vector<shared_ptr<cPeriodInfo<T>>> cSchedule<T>::OverlapMax() const
   {
      vector<shared_ptr<cPeriodInfo<T>>> periods;

      for (auto iter = m_sortedPeriods.cbegin(); iter != m_sortedPeriods.cend(); iter++)
      {
         if ((*iter)->OverlapCount() == m_maxOverlapCount)
         {
            periods.push_back(*iter);
         }
      }

      return periods;
   }
   
   /// <summary>
   /// Returns the collection of time periods that have the lowest overlap count.
   /// </summary>
   template<typename T>
   vector<shared_ptr<cPeriodInfo<T>>> cSchedule<T>::OverlapMin() const
   {
      vector<shared_ptr<cPeriodInfo<T>>> periods;
      int minOverlap = CalcMinOverlapCount();

      for (auto iter = m_sortedPeriods.cbegin(); iter != m_sortedPeriods.cend(); iter++)
      {
         if ((*iter)->OverlapCount() == minOverlap)
         {
            periods.push_back(*iter);
         }
      }

      return periods;
   }
   
   /// <summary>
   /// Returns the collection of time periods, sorted by start time.
   /// </summary>
   template<typename T>
   vector<shared_ptr<cPeriodInfo<T>>> cSchedule<T>::Periods() const
   {
      vector<shared_ptr<cPeriodInfo<T>>> periods;

      periods.reserve(m_sortedPeriods.size());
      copy(m_sortedPeriods.begin(), m_sortedPeriods.end(), back_inserter(periods));

      return periods;
   }
   
   /// <summary>
   /// The collection of time periods, sorted by start time, that have an
   /// overlap count that falls between the two given values.
   /// </summary>
   template<typename T>
   vector<shared_ptr<cPeriodInfo<T>>> cSchedule<T>::Periods(int minOverlap, int maxOverlap) const
   {
      vector<shared_ptr<cPeriodInfo<T>>> periods;

      for (auto iter = m_sortedPeriods.cbegin(); iter != m_sortedPeriods.cend(); iter++)
      {
         if (((*iter)->OverlapCount() >= minOverlap) &&
             ((*iter)->OverlapCount() <= maxOverlap))
         {
            periods.push_back(*iter);
         }
      }

      return periods;
   }

#pragma endregion

#pragma region Add Period
   
   /// <summary>
   /// Adds a time period to the schedule. Any overlapping periods that
   /// are currently present in the schedule are combined.
   /// </summary>
   /// <param name="start">The period start time.</param>
   /// <param name="stop">The period stop time.</param>
   /// <param name="content">Optional content associated with the period.</param>
   template<typename T>
   void cSchedule<T>::AddPeriod(cJulian start, cJulian stop, const vector<shared_ptr<T>>* content)
   {
      if (content != nullptr)
      {
         auto period = make_shared<cPeriodInfo<T>>(start, stop, *content);
         AddPeriod(period);
      }
      else
      {
         auto period = make_shared<cPeriodInfo<T>>(start, stop);
         AddPeriod(period);
      }
   }
   
   /// <summary>
   /// Adds a time period to the schedule. Any overlapping periods that
   /// are currently present in the schedule are combined.
   /// </summary>
   /// <param name="period">The time period to add.</param>
   template <typename T>
   void cSchedule<T>::AddPeriod(const shared_ptr<cPeriodInfo<T>>& period)
   {
      bool inBounds = (period->Stop().ToTime()  >= m_minTime.ToTime()) &&
                      (period->Start().ToTime() <= m_maxTime.ToTime());

      m_minTime = period->Start().ToTime() < m_minTime.ToTime() ? period->Start() : m_minTime;
      m_maxTime = period->Stop().ToTime()  > m_maxTime.ToTime() ? period->Stop()  : m_maxTime;

      if (!inBounds)
      {
         ProcessSingle(period);
      }
      else
      {
         m_stack.push(period);

         // Compare the new period with each existing period in the
         // master sorted list. Additional periods that are created during
         // the comparison process are pushed onto the stack for later
         // processing.
         while ((m_sortedPeriods.size() > 0) && (m_stack.size() > 0))
         {
            shared_ptr<cPeriodInfo<T>> a = m_sortedPeriods[0];
            shared_ptr<cPeriodInfo<T>> b = m_stack.top();
            m_stack.pop();

            m_sortedPeriods.erase(m_sortedPeriods.begin());
            Process(a, b);
         }
      }
      
      // Place any remaining periods into the "complete" bucket
      copy(m_sortedPeriods.begin(), m_sortedPeriods.end(), back_inserter(m_processed));

      // Pop stack to "complete" bucket
      while (!m_stack.empty())
      {
         m_processed.push_back(m_stack.top());
         m_stack.pop();
      }

      // The processed list now becomes the main sorted list.
      // Note: the main list is always empty at this point.
      m_sortedPeriods.clear();
      copy(m_processed.begin(), m_processed.end(), back_inserter(m_sortedPeriods));
      m_processed.clear();

      // Maintain sorted order
      sort(m_sortedPeriods.begin(), m_sortedPeriods.end(), cPeriodInfo<T>::Start_LT);
   }
   
   /// <summary>
   /// Adds time periods to the schedule. Any overlapping periods that
   /// are currently present in the schedule are combined.
   /// </summary>
   template<typename T>
   void cSchedule<T>::AddPeriod(const vector<shared_ptr<cPeriodInfo<T>>>& periods)
   {
      for (auto iter = periods.cbegin(); iter != periods.cend(); iter++)
      {
         AddPeriod(*iter);
      }
   }

#pragma endregion

#pragma region Process
   
   /// <summary>
   /// Process two time periods by breaking any overlapping portions into
   /// separate time periods.
   /// </summary>
   /// <param name="a">Assumed to be from a list of sorted, non-overlapping periods.</param>
   /// <param name="b">New period being added.</param>
   template <typename T>
   void cSchedule<T>::Process(const shared_ptr<cPeriodInfo<T>>& a,
                              const shared_ptr<cPeriodInfo<T>>& b)
   {
      if (a->Overlaps(b) || b->Overlaps(a))
      {
         ProcessOverlap(a, b);
      }
      else
      {
         ProcessDisjoint(a, b);
      }
   }
   
   template <typename T>
   void cSchedule<T>::ProcessOverlap(const shared_ptr<cPeriodInfo<T>>& a, 
                                     const shared_ptr<cPeriodInfo<T>>& b)
   {
      // Any two overlapping periods can be split into 3 sub-periods,
      // which are defined by 4 times.
      cJulian t1 = (a->Start().ToTime() < b->Start().ToTime()) ? a->Start() : b->Start();
      cJulian t2 = (a->Start().ToTime() > b->Start().ToTime()) ? a->Start() : b->Start();
      cJulian t3 = (a->Stop().ToTime()  < b->Stop().ToTime())  ? a->Stop()  : b->Stop();
      cJulian t4 = (a->Stop().ToTime()  > b->Stop().ToTime())  ? a->Stop()  : b->Stop();

      cJulian t2m1 = t2; // time2 minus 1 sec
      t2m1.AddSec(-1);
      cJulian t3p1 = t3; // time3 plus 1 sec
      t3p1.AddSec(1);

      // If period a and period b have the same start/stop times,
      // head and tail will both point to period "a".
      shared_ptr<cPeriodInfo<T>> head = (a->Start().ToTime() < b->Start().ToTime()) ? a : b;
      shared_ptr<cPeriodInfo<T>> tail = (a->Stop().ToTime()  > b->Stop().ToTime())  ? a : b;

      // The first sub-period
      if (t1.ToTime() <= t2m1.ToTime())
      {
         auto p1 = make_shared<cPeriodInfo<T>>(t1, t2m1, head->OverlapCount(), *head);

         m_processed.push_back(p1);
      }

      // The second sub-period
      int olapCount = a->OverlapCount() + b->OverlapCount();
      auto p2 = make_shared<cPeriodInfo<T>>(t2, t3, olapCount, *a);

      m_maxOverlapCount = max(m_maxOverlapCount, olapCount);

      vector<shared_ptr<T>> con = b->Content();

      p2->AddContent(con);

      m_processed.push_back(p2);

      // The third sub-period
      if (t3p1.ToTime() <= t4.ToTime())
      {
         auto p3 = make_shared<cPeriodInfo<T>>(t3p1, t4, tail->OverlapCount(), *tail);

         if (a->Stop().ToTime() < b->Stop().ToTime())
         {
            // Remainder of period B
            m_stack.push(p3);
         }
         else
         {
            // Remainder of period A
            m_processed.push_back(p3);
         }
      }
   }

   /// <summary>
   /// Process two periods that are completely non-overlapping.
   /// </summary>
   template<typename T>
   void cSchedule<T>::ProcessDisjoint(const shared_ptr<cPeriodInfo<T>>& a, 
                                      const shared_ptr<cPeriodInfo<T>>& b)
   {
      // No more work for A
      m_processed.push_back(a);

      // Continue processing B
      m_stack.push(b);

      if (m_maxOverlapCount == 0)
      {
         // First period being added to schedule
         m_maxOverlapCount = 1;
      }
   }
   
   template<typename T>
   void cSchedule<T>::ProcessSingle(const shared_ptr<cPeriodInfo<T>>& a)
   {
      // No more work for A
      m_processed.push_back(a);

      if (m_maxOverlapCount == 0)
      {
         // First period being added to schedule
         m_maxOverlapCount = 1;
      }
   }

   template<typename T>
   int cSchedule<T>::CalcMinOverlapCount() const
   {
      int minCount = m_maxOverlapCount;

      for (auto item = m_sortedPeriods.cbegin(); item != m_sortedPeriods.cend(); item++)
      {
         minCount = min(minCount, (*item)->OverlapCount());
      }

      return minCount;
   }

#pragma endregion

#pragma endregion

#pragma region PeriodInfo

#pragma region Properties

   /// <summary>
   /// The period overlap count.
   /// </summary>
   template<typename T>
   int cPeriodInfo<T>::OverlapCount() const { return m_overlapCount; }

   /// <summary>
   /// The content list associated with the time period.
   /// </summary>
   template<typename T>
   vector<shared_ptr<T>> cPeriodInfo<T>::Content() const 
   {
      return m_content;
   }

   /// <summary>
   /// Adds items to the time period's content list.
   /// </summary>
   /// <param name="items">The items to add.</param>
   template<typename T>
   void cPeriodInfo<T>::AddContent(const vector<shared_ptr<T>>& items)
   {
      m_content.reserve(m_content.size() + items.size());
      copy(items.begin(), items.end(), back_inserter(m_content));
   }

   /// <summary>
   /// Adds an item to the time period's content list.
   /// </summary>
   /// <param name="item">The item to add.</param>
   template<typename T>
   void cPeriodInfo<T>::AddContent(const shared_ptr<T>& item)
   {
      if (item != nullptr)
      {
         m_content.push_back(item);
      }
   }

#pragma endregion

#pragma region Construction

   // Private construction helper
   template<typename T>
   void cPeriodInfo<T>::CommonConstruct(cJulian start, cJulian stop)
   {
      if (stop.Date() < start.Date())
      {
         throw invalid_argument("Start time must be before stop time");
      }

      //Round times to nearest second
      m_start = ToNearestSecond(start);
      m_stop  = ToNearestSecond(stop);

      m_overlapCount = 1;
   }

   /// <summary>
   /// Standard constructor.
   /// </summary>
   template<typename T>
   cPeriodInfo<T>::cPeriodInfo(cJulian start, cJulian stop)
   {
      CommonConstruct(start, stop);
   }

   /// <summary>
   /// Constructor accepting content item.
   /// </summary>
   template<typename T>
   cPeriodInfo<T>::cPeriodInfo(cJulian start, cJulian stop, const shared_ptr<T>& content)
   {
      CommonConstruct(start, stop);

      if (content != NULL)
      {
         AddContent(content);
      }
   }

   /// <summary>
   /// Constructor accepting content items.
   /// </summary>
   template <typename T>
   cPeriodInfo<T>::cPeriodInfo(cJulian start, cJulian stop, const vector<shared_ptr<T>>& contents)
   {
      CommonConstruct(start, stop);
      AddContent(contents);
   }
   
   /// <summary>
   /// Internal constructor.
   /// </summary>
   template <typename T>
   cPeriodInfo<T>::cPeriodInfo(cJulian start, cJulian stop, int overlapCount, const cPeriodInfo<T>& contents)
   {
      CommonConstruct(start, stop);
      m_overlapCount = overlapCount;
      m_content.reserve(contents.m_content.size());
      copy(contents.m_content.begin(), contents.m_content.end(), back_inserter(m_content));
   }

#pragma endregion

#pragma region Utility

   /// <summary>
   /// Returns true if the given period overlaps in time.
   /// </summary>
   template <typename T>
   bool cPeriodInfo<T>::Overlaps(const shared_ptr<cPeriodInfo<T>>& p) const
   {
      return (m_stop.Date()  >= p->m_start.Date()) &&
             (m_start.Date() <= p->m_stop.Date());
   }

   /// <summary>
   /// Returns true if the start time of the first period is less than the second.
   /// </summary>
   template <typename T>
   int cPeriodInfo<T>::Start_LT(const shared_ptr<cPeriodInfo<T>>& px,
                                const shared_ptr<cPeriodInfo<T>>& py)
   {
      return (px->m_start.Date() < py->m_start.Date()) ? 1 : 0;
   }

   /// <summary>
   /// Compares periods based on their overlap counts.
   /// </summary>
   template <typename T>
   int cPeriodInfo<T>::OverlapCount_LT(const shared_ptr<cPeriodInfo<T>>& px, 
                                       const shared_ptr<cPeriodInfo<T>>& py)
   {
      return (px->m_overlapCount < py->m_overlapCount) ? 1 : 0;
   }

   /// <summary>
   /// Compares periods based on their overlap counts.
   /// </summary>
   template <typename T>
   int cPeriodInfo<T>::OverlapCount_GT(const shared_ptr<cPeriodInfo<T>>& px, 
                                       const shared_ptr<cPeriodInfo<T>>& py)
   {
      return (px->m_overlapCount > py->m_overlapCount) ? 1 : 0;
   }


   /// <summary>
   /// Shows the start, stop times and the period overlap count.
   /// </summary>
   template <typename T> 
   string cPeriodInfo<T>::ToString() const
   {
      char buf[32];
      char dateFormat[] = "%Y-%m-%d %H:%M:%S";
      
      tm tmGmtStart;
      tm tmGmtStop;
      time_t timeStart = m_start.ToTime();
      time_t timeStop  = m_stop.ToTime();

      gmtime_s(&tmGmtStart, &timeStart);
      gmtime_s(&tmGmtStop, &timeStop);

      stringstream result;
      
      strftime(buf, sizeof(buf), dateFormat, &tmGmtStart);
      result << buf;
      result << " ";

      strftime(buf, sizeof(buf), dateFormat, &tmGmtStop);
      result << buf;
      result << " : ";

      result << this->m_overlapCount;

      return result.str();
   }


#pragma endregion

#pragma endregion

}
}
}
