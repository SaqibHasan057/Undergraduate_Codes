angular.module('myIonicApp', ['ionic', 'myIonicApp.controllers','myIonicApp.services',"chart.js",'ngCordova'])

.constant('ApiEndpoint',{
  url: 'http://localhost:8100/api/'
})

.value('user', {
    user_name:"test",
    user_id:"test",
    age:0,
    email_id:"test",
    area_name:"Mohammadpur",
    current_area:"Mohammadpur",
    admin_priviledge:"1"
})






.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    if (window.cordova && window.cordova.plugins.Keyboard) {
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
      cordova.plugins.Keyboard.disableScroll(true);
    }
    if (window.StatusBar) {
      StatusBar.styleDefault();
    }
  });
})

.config(function($stateProvider, $urlRouterProvider) {

  $stateProvider
    .state('app', {
    url: '/app',
    abstract: true,
    templateUrl: 'templates/menu.html',
   controller: 'AppCtrl'
  })

  
  
  .state('enter', {
    url: '/enter',
    templateUrl: 'templates/enter.html',
    controller: 'EnterCtrl'
  })

  .state('register', {
    url: '/register',
    templateUrl: 'templates/register.html',
    controller: 'RegisterCtrl' 
  })

  .state('mainMenu', {
    url: '/mainMenu',
    templateUrl: 'templates/mainMenu.html',
    controller: 'MainMenuCtrl' 
  })

  .state('contactShow', {
    url: '/contactShow',
    templateUrl: 'templates/contactShow.html',
    controller: 'ContactShowCtrl' 
  })

  .state('adSelect', {
    url: '/adSelect',
    templateUrl: 'templates/adSelect.html',
    controller: 'AdSelectCtrl' 
  })


  .state('complaint', {
    url: '/complaint',
    templateUrl: 'templates/complaint.html',
    controller: 'ComplaintCtrl' 
  })

  .state('postAd', {
    url: '/postAd',
    templateUrl: 'templates/postAd.html',
    controller: 'PostAdCtrl' 
  })

  .state('seeAd', {
    url: '/seeAd',
    templateUrl: 'templates/seeAd.html',
    controller: 'SeeAdCtrl' 
  })

  .state('map', {
    url: '/map',
    templateUrl: 'templates/map.html',
    controller: 'MapCtrl'
  })

  .state('statisticsChoice', {
    url: '/statisticsChoice',
    templateUrl: 'templates/statisticsChoice.html',
    controller: 'StatisticsChoiceCtrl' 
  })

  .state('rawStatistics', {
    url: '/rawStatistics',
    templateUrl: 'templates/rawStatistics.html',
    controller: 'RawStatisticsCtrl' 
  })

  .state('diagrams', {
    url: '/diagrams',
    templateUrl: 'templates/diagrams.html',
    controller: 'DiagramsCtrl' 
  })

  .state('comparisionChoice', {
    url: '/comparisionChoice',
    templateUrl: 'templates/comparisionChoice.html',
    controller: 'ComparisionChoiceCtrl' 
  })

  .state('tableCompare', {
    url: '/tableCompare',
    templateUrl: 'templates/tableCompare.html',
    controller: 'TableCompareCtrl' 
  })

  .state('pieCompare', {
    url: '/pieCompare',
    templateUrl: 'templates/pieCompare.html',
    controller: 'PieCompareCtrl' 
  })

  .state('barCompare', {
    url: '/barCompare',
    templateUrl: 'templates/barCompare.html',
    controller: 'BarCompareCtrl' 
  })


  // if none of the above states are matched, use this as the fallback
  $urlRouterProvider.otherwise('/enter');
});
