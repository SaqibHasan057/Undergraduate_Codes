var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('MainMenuCtrl',function($scope,$state,$http,ApiEndpoint,user){
    //$scope.header = "Sign Up here";
    $scope.user_info = user;
    console.log($scope.user_info);
    console.log(user["user_name"])

    $scope.allimages = [{
        'src' : 'img/AnikMeme.png'
    }, {
        'src' : 'img/ionic.png'
    }];
    $scope.advertisement= function(){
        $state.go('adSelect')
	};

    $scope.complaint = function(){
        $state.go('complaint')
    }

    $scope.statistics = function(){
        $state.go('statisticsChoice')
    }

    $scope.contacts = function(){
        $state.go('contactShow')
    }

     $scope.goMap = function(){
        $state.go('map')
    }

    $scope.return = function(){
        $state.go('enter')
    }
    
})