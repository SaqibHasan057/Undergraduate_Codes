var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('MapCtrl', function($scope, $state, $cordovaGeolocation,user,$cordovaToast) {
  var options = {timeout: 10000, enableHighAccuracy: true};

 
  $cordovaGeolocation.getCurrentPosition(options).then(function(position){

  
 
    var latLng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
 
    var mapOptions = {
      center: latLng,
      zoom: 16,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    };


 
    $scope.map = new google.maps.Map(document.getElementById("map"), mapOptions);

    var pos = {};
    pos["Mohammadpur"]=[23.7658, 90.3584];
    pos["Dhanmondi"]=[23.7465, 90.3760];
    pos["Shahjahanpur"]=[23.7408, 90.4213];
    pos["Gulshan"]=[23.7925, 90.4078];
    pos["Mirpur"]=[23.8223, 90.3654];
    var markerArray = [];


    for(x in pos){
    var point = new google.maps.LatLng(pos[x][0], pos[x][1]);
     var marker = new google.maps.Marker({
      map: $scope.map,
      animation: google.maps.Animation.DROP,
      position: point,
      content: x}); 
 

     marker.addListener('click', function() {             
       console.log(this.content); 
       user["current_area"]=this.content;
       console.log(user["current_area"]);
       $state.go('mainMenu');
       
  });  
    }

         
 
 

 
  }, function(error){
    console.log("Could not get location");
  });


  
    $scope.return = function(){
        $state.go('enter')
    }

  



  

});