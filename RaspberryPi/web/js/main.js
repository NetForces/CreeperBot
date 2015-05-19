var RobotIP="localhost:4567"

$(function() {
	$('#eye_switch input').switchButton();
	$('#light_switch input').switchButton();
	$('#strobe_switch input').switchButton();
	
	// Set default state
	$.ajax({ url: "http://"+RobotIP+"/EyesOff" });
	$.ajax({ url: "http://"+RobotIP+"/LightOff" });
	
	// Eyes switch action
	$('#eye_switch').change(function() {
		if($('#eye').is(':checked'))
		{
			$.ajax({ url: "http://"+RobotIP+"/EyesOn" });
		}
		else
		{
			$.ajax({ url: "http://"+RobotIP+"/EyesOff" });			
		}
	});
	
	// Light switch action
	$('#light_switch').change(function() {
		if($('#light').is(':checked'))
		{
			$.ajax({ url: "http://"+RobotIP+"/LightOn" });
		}
		else
		{
			$.ajax({ url: "http://"+RobotIP+"/LightOff" });			
		}
	});
	
	// Strobe switch action
	$('#strobe_switch').change(function() {
		if($('#strobe').is(':checked'))
		{
			$.ajax({ url: "http://"+RobotIP+"/LightStrobe" });
		}
		else
		{
			$.ajax({ url: "http://"+RobotIP+"/LightOff" });			
		}
	});
	
	// Move forward action
	$('#front').click(function() {
		$.ajax({ url: "http://"+RobotIP+"/Front" });
	});
	
	// Move right action
	$('#right').click(function() {
		$.ajax({ url: "http://"+RobotIP+"/Right" });
	});
	
	// Move left action
	$('#left').click(function() {
		$.ajax({ url: "http://"+RobotIP+"/Left" });
	});
	
	// Move backward action
	$('#back').click(function() {
		$.ajax({ url: "http://"+RobotIP+"/Back" });
	});
	
	// Stop action
	$('#stop').click(function() {
		$.ajax({ url: "http://"+RobotIP+"/Stop" });
	});
});
