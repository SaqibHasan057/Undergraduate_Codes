var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('AdSelectCtrl',function($scope,$state,$http,ApiEndpoint){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.postAd= function(){
        $state.go('postAd')
	};

    $scope.seeAd = function(){
        $state.go('seeAd')
    }

    $scope.return = function(){
        $state.go('mainMenu')
    }
    
})