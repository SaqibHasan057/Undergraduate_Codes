var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('EnterCtrl',function($scope,$state,$http,ApiEndpoint,$ionicPopup,user){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.login = function()
	{

        if($scope.data.password=="" || $scope.data.email==""){
            var alert = $ionicPopup.alert({ title: 'Input error', template:'Please input all the fields properly!!'});
            return;
        }
        var jsonreq = JSON.stringify({
        password:$scope.data.password,
        email_id:$scope.data.email
        });
        var url = ApiEndpoint.url+ 'login/';
        $http.post(url,jsonreq).then(function successCallback(response){
            console.log(response.data);
            
            if(response.data=="Fail"){
                 var alert = $ionicPopup.alert({ title: 'Mismatch', template:'Your password does not match with the email provided!!'});
            }
            else if(response.data=="Non-existent"){
                var alert = $ionicPopup.alert({ title: 'Invalid user', template:'No such user exists!!'});
            }
            else{
                $scope.user_info=response.data;
              user["user_name"]=$scope.user_info[0]["user_name"];
              user["user_id"]=$scope.user_info[0]["user_id"];
              user["age"]=$scope.user_info[0]["age"];
              user["email_id"]=$scope.user_info[0]["email_id"];
              user["area_name"]=$scope.user_info[0]["area_name"];
              user["current_area"]=$scope.user_info[0]["area_name"];
              user["admin_priviledge"]=$scope.user_info[0]["admin_priviledge"];
              console.log(user["user_name"]);
              var date = new Date();
              console.log(date);
                $state.go('mainMenu');
            }

        },function errorCallback(response){
            console.log("ERROR");
            var alert = $ionicPopup.alert({ title: 'Server side Problem', template:'Server could not be connected!!Try again correctly'});
        });
	};

    $scope.registration = function(){
        $state.go('register');
    }
    
})