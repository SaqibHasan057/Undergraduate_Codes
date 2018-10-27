var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('DiagramsCtrl',function($scope,$state,$http,ApiEndpoint,user){

   $scope.current_area = user["current_area"];

   var jsonreq = JSON.stringify({
            area_name:user["current_area"]
            });
    var url = ApiEndpoint.url+ 'getRawStatistics/';
    $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
                $scope.crime = response.data
                console.log($scope.crime[0].number_of_murder)
                $scope.totalCrime = $scope.crime[0].number_of_murder + $scope.crime[0].number_of_theft + $scope.crime[0].number_of_robbery + $scope.crime[0].number_of_terrorism + $scope.crime[0].number_of_rape
                 $scope.labels = ["Murder", "Rape", "Theft", "Robbery", "Terrorism"];
  $scope.series = [$scope.crime[0].area_name];
  $scope.data = [
    $scope.crime[0].number_of_murder,$scope.crime[0].number_of_theft,$scope.crime[0].number_of_robbery,$scope.crime[0].number_of_terrorism,$scope.crime[0].number_of_rape
  ];
    },function errorCallback(response){
                console.log("ERROR");
    });
   
  
  $scope.onClick = function (points, evt) {
    console.log(points, evt);
  };

  
    $scope.return = function(){
        $state.go('statisticsChoice')
    }
  
  
    
})