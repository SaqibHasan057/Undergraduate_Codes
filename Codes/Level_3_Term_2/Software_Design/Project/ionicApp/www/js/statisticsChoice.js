var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('StatisticsChoiceCtrl',function($scope,$state,$http,ApiEndpoint,user){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    console.log($scope.user_info);
    console.log(user["user_name"])

    $scope.RawStatistics= function(){
        $state.go('rawStatistics')
	};

    $scope.Diagrams = function(){
        $state.go('diagrams')
    }

    $scope.Comparision = function(){
        $state.go('comparisionChoice')
    }

    
    $scope.return = function(){
        $state.go('mainMenu')
    }

    
})