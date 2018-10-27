var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('LoginCtrl',function($scope,$state,$http,ApiEndpoint,shareDataService){
    $scope.url = ApiEndpoint+'/smugglers';
    $scope.data = {};
    $scope.login = function()
	{
        var jsonreq = JSON.stringify({user:$scope.data.username,password:$scope.data.password});
        var url = ApiEndpoint.url+ 'register/';
        $http.post(url,jsonreq).then(function successCallback(response){
             for(var r in response.data) {
               var smugler = response.data[r];
               shareDataService.addList(smugler);
               console.log(smugler);
             }
           
        },function errorCallback(response){
            console.log("ERROR");
        });
        
		$state.go('app.home');
	};
    
})

module.service('shareDataService', function() {
  var myList = [];

  var addList = function(newObj) {
      myList.push(newObj);
  }

  var getList = function(){
      return myList;
  }

  return {
    addList: addList,
    getList: getList
  };

});
