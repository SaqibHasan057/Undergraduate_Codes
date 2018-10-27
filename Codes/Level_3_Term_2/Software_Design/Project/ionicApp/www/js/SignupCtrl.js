var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('SignupCtrl',function($scope,$state,$http,ApiEndpoint){
    $scope.header = "Sign Up here";
    $scope.data = {};
    $scope.signup = function()
	{
        var jsonreq = JSON.stringify({
            firstname:$scope.data.firstname,
            surname:$scope.data.surname,
            email:$scope.data.email,
            password:$scope.data.password,
            city:$scope.data.city,
            sex:$scope.data.sex,
            phoneno:$scope.data.phone
        });
        var url = ApiEndpoint.url+ 'register/';
        $http.post(url,jsonreq).then(function successCallback(response){
             console.log(response.data);
           
        },function errorCallback(response){
            console.log("ERROR");
        });
        
		$state.go('app.home');
	};
    
})