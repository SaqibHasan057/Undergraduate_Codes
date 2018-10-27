var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('MainMenuCtrl',function($scope,$state,$http,ApiEndpoint){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.advertisement= function(){
        $state.go('addSelect')
	};

    $scope.complain = function(){
        $state.go('complaint')
    }
    
})