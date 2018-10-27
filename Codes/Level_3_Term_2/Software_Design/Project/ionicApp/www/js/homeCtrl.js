var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('HomeCtrl',function($scope,$http,$state,$ionicPopup,ApiEndpoint,shareDataService){
    //$scope.header = "Welcome to the galaxy's finest smugglers";
    $scope.smuglers = shareDataService.getList();
    
	$scope.logout = function(){
		$state.go('login');
	}
})
