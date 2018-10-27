var module = angular.module('starter.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('LoginCtrl',function($scope,$state,$http,ApiEndpoint){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.login = function()
	{
        if($scope.data.password==$scope.data.confirm_password){
            var jsonreq = JSON.stringify({
            area_id:$scope.data.area_id,
            username:$scope.data.username,
            password:$scope.data.password,
            age:$scope.data.age
            });
            var url = ApiEndpoint.url+ 'register/';
            $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
            },function errorCallback(response){
                console.log("ERROR");
            });
            $state.go('tab.chats');
        }
        else console.log("Passwords do not match!!");
       
	};

    $scope.registration = function(){
        $state.go('register')
    }
    
})