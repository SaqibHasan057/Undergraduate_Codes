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
       
            var jsonreq = JSON.stringify({
            description:$scope.data.description,
            type:$scope.data.type,
            email_id:$scope.data.email,
            phone_no:$scope.data.phone,
            link_to_website:$scope.data.link,
            date_of_issue:new Date()
            });
            var url = ApiEndpoint.url+ 'addAdvertisement/';
            $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
                $state.go('adSelect');
            },function errorCallback(response){
                console.log("ERROR");
            });
       
	};

    $scope.return = function(){
        $state.go('adSelect')
    }
    
})