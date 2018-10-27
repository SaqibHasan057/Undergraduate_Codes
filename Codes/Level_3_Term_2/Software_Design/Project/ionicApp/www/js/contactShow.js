var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('ContactShowCtrl',function($scope,$state,$http,ApiEndpoint,user){
    //$scope.header = "Sign Up here";
    $scope.data = {};


    var jsonreq = JSON.stringify({
            area_name:user["current_area"]
            });
    var url = ApiEndpoint.url+ 'getContact/';
    $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
                $scope.contact = response.data
    },function errorCallback(response){
                console.log("ERROR");
    });



    $scope.postAdvertisement = function()
	{
       
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
       
	};

    $scope.return = function(){
        $state.go('mainMenu')
    }
    
})