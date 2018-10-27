var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('ComplaintCtrl',function($scope,$state,$http,ApiEndpoint,user){
    //$scope.header = "Sign Up here";
    $scope.data = {};
    console.log("Touche!!")

    function compareDate(a,b){
    var date1 = new Date(a.date_of_issue);
    var date2 = new Date(b.date_of_issue);
    
    if(date1<date2)return 1;
    else if(date1>date2)return -1;
    else return 0;}

    var url = ApiEndpoint.url+ 'getComplaint/';
        $http.get(url).then(function successCallback(response){




           





            console.log(response.data);
            $scope.data = response.data;


            var a = $scope.data[0];
            var b = $scope.data[1];
            var x  = compareDate(a,b);
            console.log(x);

            var newJSONArray=[];

            for(var i=0; i<$scope.data.length; i++){
                var obj = $scope.data[i];
                newJSONArray.push(obj);
            }

            newJSONArray.sort(compareDate);

            for(var i =0; i<newJSONArray.length;i++){
                console.log(newJSONArray[i]['date_of_issue']);
            }

            $scope.database=newJSONArray;
        },function errorCallback(response){
            console.log("ERROR");
        });


    $scope.postComplaint = function()
    {
      
            var jsonreq = JSON.stringify({
            area_name:$scope.data.area_name,
            user_id:user['user_id'],
            description:$scope.data.description,
            tag:$scope.data.tag,
            date_of_issue:new Date(),
            });
            var url = ApiEndpoint.url+ 'addComplaint/';
            $http.post(url,jsonreq).then(function successCallback(response){
                console.log(response.data);
            },function errorCallback(response){
                console.log("ERROR");
            });

       
    };

    $scope.return = function(){
        $state.go('mainMenu')
    }
    
})