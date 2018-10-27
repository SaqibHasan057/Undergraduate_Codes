var module = angular.module('myIonicApp.controllers');

module.config(['$httpProvider',function($httpProvider){
	$httpProvider.defaults.xsrfCookieName = 'csrftoken';
	$httpProvider.defaults.xsrfHeaderName = 'X-CSRFToken';
}])

module.controller('BarCompareCtrl',function($scope,$state,$http,ApiEndpoint,user){


 var url = ApiEndpoint.url+ 'getAllStatistics/';
        $http.get(url).then(function successCallback(response){
            console.log(response.data);
            $scope.allVals=response.data;


            var eachCrimeLabel=[];
            var eachCrimeSeries=["Murder","Rape","Robbery","Theft","Terrorism"];
            var eachCrimeData=[ 
            [],
            [],
            [],
            [],
            [] 
            ];

            var totalCrimeLabel=[];
            var rapeLabel=[];
            var murderLabel=[];
            var terrorismLabel=[];
            var robberyLabel=[];
            var theftLabel=[];

            var totalCrimeData=[];
            var rapeData=[];
            var murderData=[];
            var terrorismData=[];
            var robberyData=[];
            var theftData=[];



            for(var i=0; i<$scope.allVals.length;i++){
                var obj = $scope.allVals[i];
                totalCrimeLabel.push(obj.area_name);
                rapeLabel.push(obj.area_name);
                murderLabel.push(obj.area_name);
                terrorismLabel.push(obj.area_name);
                robberyLabel.push(obj.area_name);
                theftLabel.push(obj.area_name);

                totalCrimeData.push(obj.total);
                rapeData.push(obj.number_of_rape);
                murderData.push(obj.number_of_murder);
                terrorismData.push(obj.number_of_terrorism);
                robberyData.push(obj.number_of_robbery);
                theftData.push(obj.number_of_theft);

                eachCrimeLabel.push(obj.area_name);

                
                eachCrimeData[0].push(obj.number_of_murder);
                eachCrimeData[1].push(obj.number_of_rape);
                eachCrimeData[2].push(obj.number_of_robbery);
                eachCrimeData[3].push(obj.number_of_theft);
                eachCrimeData[4].push(obj.number_of_terrorism);

            }
           

            $scope.totalCrimeLabel=totalCrimeLabel;
            $scope.rapeLabel=rapeLabel;
            $scope.murderLabel=murderLabel
            $scope.terrorismLabel=terrorismLabel;
            $scope.robberyLabel=robberyLabel;
            $scope.theftLabel=theftLabel;

            $scope.totalCrimeData=totalCrimeData;
            $scope.rapeData=rapeData;
            $scope.murderData=murderData;
            $scope.terrorismData=terrorismData;
            $scope.robberyData=robberyData;
            $scope.theftData=theftData;

            $scope.eachCrimeLabel=eachCrimeLabel;
            $scope.eachCrimeData=eachCrimeData;
            $scope.eachCrimeSeries=eachCrimeSeries;

            $scope.options = {legend: {display: true}};

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