var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('PostAdCtrl',function($scope,$state,$http,ApiEndpoint){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.postAdvertisement = function()
	{
        if($scope.data.password==$scope.data.confirm_password){
            var jsonreq = JSON.stringify({
            description:$scope.data.description,
            type:$scope.data.type,
            email_id:$scope.data.email,
            phone_no:$scope.data.phone,
            link_to_website:$scope.data.link
            });
            var url = ApiEndpoint.url+ 'addAdvertisement/';
            $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
                $state.go('adSelect');
            },function errorCallback(response){
                console.log("ERROR");
            });
            
        }
        else console.log("Passwords do not match!!");
       
	};
    
})