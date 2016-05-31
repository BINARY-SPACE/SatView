var DeltaHeight=0;

function FP_callJS() { // v1.0
	eval(arguments[0]);
}

function onRecalcLayout() {
	var pagetemplate=document.getElementById("PageTemplate");
	var pagetext=document.getElementById("PageText");
	var pagesection=document.getElementById("HowDoISection");
	var pagefloater=document.getElementById("PageFloater");
	var pagefooter=document.getElementById("PageFooter");
	
	for (DeltaHeight = (pagesection.clientHeight > 0) ? (parseInt(pagetemplate.style.height)-getVertPosition(pagefooter)+pagesection.clientHeight+parseInt(pagetext.style.marginBottom)):0; parseInt(pagefloater.style.top)-getVertPosition(pagefooter) > 0; ) {
		pagetext.style.height = parseInt(pagefloater.style.top)-getVertPosition(pagetext);
		break;
	}
	FP_callJS("onDynamicLayout()");
}

function onDynamicLayout() {
	var pagetext=document.getElementById("PageText");
	var pagesection=document.getElementById("HowDoISection");
	var pagefloater=document.getElementById("PageFloater");
	var pagefooter=document.getElementById("PageFooter");
	
	for (pagefooter.style.top = (DeltaHeight > 0) ? Math.max(pagesection.clientHeight-DeltaHeight,0):pagefooter.style.top; (offset = getVertPosition(pagefooter)-parseInt(pagefloater.style.top)) > 0; ) {	
		pagefloater.style.height = offset;
		pagefloater.style.display = "block";
		FP_callJS("redraw()");
		return;
	}
	for (pagefloater.style.display = "none",pagefloater.style.height = 0; parseInt(pagefloater.style.top)-getVertPosition(pagefooter) > 0; ) {
		pagetext.style.height = parseInt(pagefloater.style.top)-getVertPosition(pagetext);
		break;
	}
}

function onClickListItem(e)
{
	var e = window.event  ||  e;
	var src = e.target || e.srcElement;
	var items = document.getElementsByTagName("*");

	for (index = 0; index < items.length; index++) {
		if (items[index] == src) {
			if (src.className == "") {
				index++;
				index++;
			}
			if (index < items.length-1) {
				items[index+1].style.display = (items[index+1].style.display == "none") ? "block":"none";
			}
			break;
		}
	}
	FP_callJS("onDynamicLayout()");
}

function getHorzPosition(obj) {
	var x=0;

    while (obj) {
		x += obj.offsetLeft;
		obj = obj.offsetParent;
    }
    return x;
}
function getVertPosition(obj) {
	var y=0;

    while (obj) {
		y += obj.offsetTop;
		obj = obj.offsetParent;
    }
    return y;
}

function redraw() {
	window.resizeBy(0,1);
	window.resizeBy(0,-1);
}
