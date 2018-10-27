var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('ComparisionChoiceCtrl',function($scope,$state,$http,ApiEndpoint,user){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    console.log($scope.user_info);
    console.log(user["user_name"])

    $scope.tableCompare= function(){
        $state.go('tableCompare')
	};

    $scope.picCompare= function(){
        $state.go('pieCompare')
    }

    $scope.barCompare= function(){
        $state.go('barCompare')
    }

    $scope.return = function(){
        $state.go('statisticsChoice')
    }
    
})