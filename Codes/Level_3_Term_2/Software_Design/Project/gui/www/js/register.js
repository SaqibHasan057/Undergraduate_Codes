var module = angular.module('starter.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('RegisterCtrl',function($scope,$state,$http,ApiEndpoint){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.register = function()
	{
        if($scope.data.password==$scope.data.confirm_password){
            var jsonreq = JSON.stringify({
            area_id:$scope.data.area_id,
            username:$scope.data.username,
            password:$scope.data.password,
            age:$scope.data.age
            email_id:$scope.data.email_id
            console.log($scope.data.area_id+$scope.data.username+$scope.data.password+$scope.data.age);
            });
            var url = ApiEndpoint.url+ 'register/';
            $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
            },function errorCallback(response){
                console.log("ERROR");
            });
            $state.go('login');
        }
        else console.log("Passwords do not match!!");
       
	};
    
})