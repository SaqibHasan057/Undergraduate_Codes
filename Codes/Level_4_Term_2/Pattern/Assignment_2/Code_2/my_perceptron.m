function w = my_perceptron(w,learn_rate,train)
  
  train_size=size(train);
  
  %examples=train(:,1:2);
  temp_result=[];
  
 
  
  count=0;
  
  count1=[];
  time=[];
  
  
  for k=1:500
    time=[time k];
    w_temp=w;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  
    for i=1:train_size(1) 
      
    %prepare x
    %find w'x
    %update w if missclassified
    %store the number of missclassified exaples in count variable
      
    end
    
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   
  
    w=w_temp;
    count1=[count1 count];
    if count==0
      break;
    end
    count=0;
    
    
  end
  
  
  
  %disp(transpose(w_temp));
  plot(time,count1);
  
  
  
  
end