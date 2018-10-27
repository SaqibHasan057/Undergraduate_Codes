/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaapplication3;

import java.util.*;
import java.lang.*;
import java.io.*;
//import java.string.*;

/**
 *
 * @author parag
 */
public class JavaApplication3 {

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     */
    
    public static double mean(double a[],int count){
        double mean;
        double sum=0;
        for(int i=0;i<count;i++){
            sum=sum+a[i];
        }
        mean=sum/count;
        return mean;        
    }
    
    public static double std(double a[],double mean, int count){
        double std;
        double sum=0;
        for(int i=0;i<count;i++){
            sum+=Math.pow(a[i]-mean,2);    
        }
        std=Math.sqrt(sum/(count-1));;
        return std;        
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        // TODO code application logic here
        double train_data[][];
        double test_data[][];
        train_data=new double[100][3];
        test_data=new double[100][3];
        
        int train_count;
        int test_count;
        
        System.out.println("Reading training data");
        
        File train=new File("train.txt");
        Scanner sc=new Scanner(train);
        int line_number=0;
        
        while(sc.hasNextLine()==true){
            String s=sc.nextLine();
            StringTokenizer t=new StringTokenizer(s);
            int token_number=0;
            while(t.hasMoreTokens()){
                train_data[line_number][token_number]=Double.parseDouble(t.nextToken());
                token_number++;
            }
            line_number++;
        }
        
        train_count=line_number;
        
        for(int i=0;i<100;i++){
            for(int j=0;j<3;j++){
                System.out.print(train_data[i][j]+" ");
            }
            System.out.println("");
        }
        
        System.out.println("Reading Test data");
        
        File test=new File("test.txt");
        sc=new Scanner(test);
        line_number=0;
        
        while(sc.hasNextLine()==true){
            String s=sc.nextLine();
            StringTokenizer t=new StringTokenizer(s);
            int token_number=0;
            while(t.hasMoreTokens()){
                test_data[line_number][token_number]=Double.parseDouble(t.nextToken());
                token_number++;
            }
            line_number++;
        }
        
        test_count=line_number;
        
        for(int i=0;i<100;i++){
            for(int j=0;j<3;j++){
                System.out.print(test_data[i][j]+" ");
            }
            System.out.println("");
        }
        
        System.out.println(train_count);
        System.out.println(test_count);
        
        double train_x[]=new double[train_count];
        double train_y[]=new double[train_count];
        int train_class[]=new int[train_count];
        
        for(int i=0;i<train_count;i++){
            train_x[i]=train_data[i][0];
            train_y[i]=train_data[i][1];
            train_class[i]=(int)train_data[i][2];
        }
        
        //calculate mean and standard deviation for class 1 and 2 here
        
        
        
        
        double test_x[]=new double[test_count];
        double test_y[]=new double[test_count];
        int test_class[]=new int[test_count];
        
        for(int i=0;i<test_count;i++){
            test_x[i]=test_data[i][0];
            test_y[i]=test_data[i][1];
            test_class[i]=(int)test_data[i][2];
        }
        
        
        //claculate the probabilities here and keep your result in res array
        
               
        int res[]=new int[100];
        
        int count=0;
        for(int i=0;i<test_count;i++){
            if(test_class[i]==res[i]){
                count++;
            }
        }
        
        System.out.println(count);
        
        
    }
    
}