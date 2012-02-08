$(document).ready(function(){
    initButtons();
});

function initButtons(){
   $('.icon').click(function(){
	id = $("img",this).attr('id');
	//id = 'play-button';
	$.ajax({
	    type: "POST",
	    url: "/play",
	    dataType: 'json',
	    data: {func: id},
	    success: function(data){ 
		buttonPressed(data,id);
	    }
	});
    });
    id = $("img",this).attr('id');
    amt = $('#height-amount').val();
    $('.lift-icon').click(function(){
    	alert("moving projector");
		$.ajax({
			type: "POST",
			url: "/lift",
			dataType: 'json',
			data: {func: id, amount: amt},
			success: function(data){
				buttonPressed(data,id);			
			}    
    });
    });
}

function buttonPressed(data,id){
    if(id=='play-button' | id=='stop-button'){
		swapPlayImage(data.status);
    }
    if(id.indexOf('lift') != -1){
		updateLift(data);    
    }
}

function swapPlayImage(status){
    if(status == 'playing'){
	$('#play-button').attr('src','static/images/icons/pause.gif');
    } else {
	$('#play-button').attr('src','static/images/icons/play.gif');
    }
}

function updateLift(data){
	$('height-data').html(data.height);
}