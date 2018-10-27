var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('RegisterCtrl',function($scope,$state,$http,ApiEndpoint,$ionicPopup){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    $scope.register = function()
	{
            if($scope.data.area_name==null || $scope.data.username==null || $scope.data.age==null || $scope.data.email==null){
                var alert = $ionicPopup.alert({ title: 'Incomplete', template:'Fill up all the info!!'});
                return;
            }
        if($scope.data.password==$scope.data.confirm_password){
            var jsonreq = JSON.stringify({
            area_name:$scope.data.area_name,
            user_name:$scope.data.username,
            password:$scope.data.password,
            age:$scope.data.age,
            email_id:$scope.data.email,
            
            });
            var url = ApiEndpoint.url+ 'register/';
            $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
                $state.go('enter');
            },function errorCallback(response){
                console.log("ERROR");
            });
            
        }
        else{
            console.log("Passwords do not match!!");
            var alert = $ionicPopup.alert({ title: 'Mismatch', template:'Passwords do not match!!'});
        }
        $state.go('enter');
       
	};

    $scope.return = function(){
        $state.go('enter')
    }

    $scope.showSelectValue = function(mySelect) {
    console.log(mySelect);
}
    
})