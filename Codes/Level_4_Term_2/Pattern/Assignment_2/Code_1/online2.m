train=load('data.txt');

w=rand(3,1);
learn_rate=0.5;
w=my_perceptron(w,learn_rate,train);
disp(w);
