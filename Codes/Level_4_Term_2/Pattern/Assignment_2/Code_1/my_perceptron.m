function w = my_perceptron(w,learn_rate,train)
  
  train_size=size(train);
  count_error=[];
  time=[];
  count=0;
  
  
  for k=1:500
    time=[time k];
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    for i=1:train_size(1)
     
    %insert your code within this for loop and record the number of
    %missclassified examples on count variable  
     
     
    end
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
  
   
    count_error=[count_error count];
    if count==0
      break;
    end
    count=0; 
  end
  
  plot(time,count_error)
   
end