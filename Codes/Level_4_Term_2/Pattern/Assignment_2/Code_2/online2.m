train=load('train.txt');
test=load('test.txt');

No_of_class=3;
No_of_attribute=2;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%set the dimension for w
w=rand(?,?);
%w=[1;1;-7]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
learn_rate=0.5;

w=my_perceptron(w,learn_rate,train);


disp(w);

test_size=size(test);

count=0;
for i=1:test_size(1) 
  %disp(i);
  t1=[test(i,1:2) 1];
  t2=[test(i,1:2) 1];
  t3=[test(i,1:2) 1];
  
  w1=w(1:3,:);
  w2=w(4:6,:);
  w3=w(7:9,:);
  
  z1=w1'*t1';
  z2=w2'*t2';
  z3=w3'*t3';
  %disp(xx);
  z=[z1 z2 z3];
  [M,I] = max(z);
      
  temp_result=I*1.0;
  %disp(temp_result);
  
  if train(i,3)==temp_result
    count=count+1; 
  end
  
end

disp(count);
