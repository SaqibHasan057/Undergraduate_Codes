angular.module('myIonicApp.services', [])

.factory('UserInfo', function() {
   var user = {user_name: "Dipto", user_id: 1, age: 22, email_ID: "a@b.com", area_name: "Lalmatia"};

   user.set = function(userName,userID,age,emailID,areaName){
       user.user_name = userName;
       user.user_id = userID;
       user.age = age;
       user.email_ID = emailID;
       user.area_name = areaName;
       console.log(userName);
   }

   return user;
   
}); 
