var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('TableCompareCtrl',function($scope,$state,$http,ApiEndpoint,user){


function compareTotal(a,b){
    if(a.total<b.total)return -1;
    else if(a.total>b.total)return 1;
    else return 0;
}

function compareRape(a,b){
    if(a.number_of_rape<b.number_of_rape)return -1;
    else if(a.number_of_rape>b.number_of_rape)return 1;
    else return 0;
}

function compareMurder(a,b){
    if(a.number_of_murder<b.number_of_murder)return -1;
    else if(a.number_of_murder>b.number_of_murder)return 1;
    else return 0;
}

function compareTerrorism(a,b){
    if(a.number_of_terrorism<b.number_of_terrorism)return -1;
    else if(a.number_of_terrorism>b.number_of_terrorism)return 1;
    else return 0;
}

function compareRobbery(a,b){
    if(a.number_of_robbery<b.number_of_robbery)return -1;
    else if(a.number_of_robbery>b.number_of_robbery)return 1;
    else return 0;
}

function compareTheft(a,b){
    if(a.number_of_theft<b.number_of_theft)return -1;
    else if(a.number_of_theft>b.number_of_theft)return 1;
    else return 0;
}




 var url = ApiEndpoint.url+ 'getAllStatistics/';
        $http.get(url).then(function successCallback(response){
            console.log(response.data);
            $scope.allVals=response.data

            var totalCrimes=[];
            var rape=[];
            var murder=[];
            var terrorism=[];
            var robbery=[];
            var theft=[]
            for(var i=0; i<$scope.allVals.length;i++){
                var obj = $scope.allVals[i];
                totalCrimes.push(obj);
                rape.push(obj);
                murder.push(obj);
                terrorism.push(obj);
                robbery.push(obj);
                theft.push(obj);
            }
            totalCrimes.sort(compareTotal);
            rape.sort(compareRape);
            murder.sort(compareMurder);
            terrorism.sort(compareTerrorism);
            robbery.sort(compareRobbery);
            theft.sort(compareTheft);

            $scope.totalCrimes=totalCrimes;
            $scope.rape=rape;
            $scope.murder=murder;
            $scope.terrorism=terrorism;
            $scope.robbery=robbery;
            $scope.theft=theft;
        },function errorCallback(response){
            console.log("ERROR");
        });
                
   
  
  $scope.onClick = function (points, evt) {
    console.log(points, evt);
  };

  
    $scope.return = function(){
        $state.go('comparisionChoice')
    }
  
  
    
})