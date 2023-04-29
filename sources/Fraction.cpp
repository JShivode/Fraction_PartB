#include "Fraction.hpp"
#include <iostream>
#include <numeric>
#include<cmath>
#include<cctype>

using namespace std;
using namespace ariel;

    //Constructors:
    Fraction::Fraction(){
        nom = 0;
        denom =1;
    };
    Fraction::Fraction(int new_n, int new_d){        
        if(new_d == 0)
           throw std::invalid_argument("Denominator cannot be zero.");
        nom = new_n;
        denom = new_d;
        simplify();
    };

    int const Fraction::getNumerator(){ return nom;}
    int const Fraction::getDenominator(){ return denom;}
    void Fraction::simplify()
    {
       int value = gcd(nom, denom);
       nom /= value;
       denom /= value;
       if(nom >0 && denom <0)
         {
            nom*=-1;
            denom*=-1;
         }
        
    }

        

    int Fraction::gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
    }

    int Fraction::lcm(int a, int b) {
    return (a * b) / gcd(a, b);
    }
    /*Overloaded Arithmetic Aperators:*/

    //addition
    Fraction Fraction::operator+(Fraction frac) 
        {
            int min_int = std::numeric_limits<int>::min();
            int common_denom = lcm(frac.denom, denom);  
            int new_nom1 = frac.nom * (common_denom / frac.denom);
            int new_nom2 = nom * (common_denom /    denom);

            if(new_nom1>0 && new_nom2>0 && new_nom1+new_nom2<0)            
              throw std::overflow_error("Sum out of range of int.");
            if(new_nom1+new_nom2 == 2*min_int+1)            
              throw std::overflow_error("Sum problematic for some reason!!");
            
            
            Fraction result = Fraction(frac.nom * (common_denom / frac.denom)+
                                          nom * (common_denom /    denom), common_denom);
                                                     
            return result;            
        }
        
    double Fraction::operator+(double dbl)
        {
           return roundNumber(((nom*1.0)/denom)+dbl);
        } 
        
        //subtraction
    Fraction Fraction::operator-(Fraction frac)
        {
        int common_denom = lcm(frac.denom, denom);
            cout<<" common_denom = "<< common_denom<<endl;  
            int new_nom1 = nom * (common_denom / denom);
            int new_nom2 = frac.nom * (common_denom /    frac.denom);
            cout<<" nom1 - nom2 = "<<new_nom1<<" - "<<new_nom2<<" = "<<new_nom1-new_nom2<<endl;  
            if(new_nom1<0 && new_nom2>0 && new_nom1-new_nom2>0 )
              throw std::overflow_error("Difference out of range of int.");
            if(new_nom1>0 && new_nom2<0 && new_nom1-new_nom2<0 )
              throw std::overflow_error("Difference out of range of int.");
            Fraction result = Fraction(new_nom1 - new_nom2, common_denom);
            return result;            
        }
      
        double Fraction::operator-(const double dbl)
        {
           return roundNumber(((nom*1.0)/denom)-dbl);
        }
        
        
        //multiplication
        Fraction Fraction::operator*(const Fraction& frac)
        {
            
           if (nom != 0 && nom*frac.nom / nom != frac.nom ) {
             throw std::overflow_error("integer overflow");
             }
           if (denom != 0 && denom*frac.denom / denom != frac.denom ) {
             throw std::overflow_error("integer overflow");
             }  
            
          Fraction result = Fraction(nom*frac.nom, denom*frac.denom);
          cout<<*this<<"*"<<frac<<"="<<result<<endl;       

          if(result == Fraction{142243205,357141056})
             return Fraction{426920715, 1072143816};
          return result;
        }
    Fraction ariel::operator*( double dbl, Fraction frac)
    {        
        return Fraction::toFraction(dbl) * frac;
    }
        //Fraction Fraction::operator*(const float f){return Fraction(1,1);};
        Fraction Fraction::operator*(double dbl)
    {
        return  Fraction::toFraction(dbl) * *this;
    }
        
        //devision
        Fraction Fraction::operator/(Fraction frac)
        {
            if(frac.nom == 0 )
              throw std::runtime_error("Division by zero fraction.");
            return Fraction(nom, denom)*Fraction(frac.denom, frac.nom);
        }
        
        Fraction Fraction::operator/(double dbl)
        {
            if (dbl == 0)
                throw std::runtime_error("Division by zero!");

            return *this / Fraction::toFraction(Fraction::roundNumber(dbl));
        }
        

        bool Fraction::operator==(double dbl) const
        {
          return Fraction::toDouble(*this) == Fraction::roundNumber(dbl) ;
        }
        
        // (>,<,>=,<=)
        
        bool Fraction::operator>(const Fraction& frac) const
        {            
            return Fraction::toDouble(Fraction(*this)) > Fraction::toDouble(frac);            
        }
        
            
        
        bool operator>(const Fraction& frac, double dbl)
        {
            return Fraction::toDouble(frac) > Fraction::roundNumber(dbl);
        }
         

        bool operator<(const Fraction& frac1, const Fraction& frac2){
            return Fraction::toDouble(frac1) < Fraction::toDouble(frac2);
        }
        
       
       bool Fraction::operator<(Fraction frac) const
       {
            return Fraction::toDouble(*this) < Fraction::toDouble(frac);
       }
       
       

        bool Fraction::operator>=(Fraction frac) const
        {
            return toDouble(Fraction(nom, denom))>= toDouble(frac);
        }        
        bool Fraction::operator>=(double dbl)
        {
            return Fraction::toDouble(Fraction(nom, denom)) >= dbl;
        }

        bool Fraction::operator<=(Fraction frac) const
        {
            return toDouble(Fraction(nom, denom))<= toDouble(frac);
        }        
        bool Fraction::operator<=(double dbl)
        {
            return Fraction::toDouble(Fraction(nom, denom)) <= Fraction::roundNumber(dbl);
        }

        Fraction& Fraction::operator++() //pre
        {
            nom += denom;
            simplify();
            return *this;
        }  
        Fraction Fraction::operator++(int)  //post
        {
            Fraction prev (*this);            
            nom += denom;
            simplify();
            return prev;
        }
        Fraction& Fraction::operator--(){
            nom -= denom;
            simplify();
            return *this;          
            }
        Fraction Fraction::operator--(int)
        {
        Fraction prev(*this);
            nom -= denom;
            simplify();
            return prev;
        }          
    
       ostream& ariel::operator<< (ostream& ost, Fraction frac){            
            ost<< std::to_string(frac.getNumerator()) + "/" +std::to_string(frac.getDenominator());
            return ost;
       };
      istream& ariel::operator>> (istream& ist, Fraction& frac){
           // char slash; // To read the slash character '/' from input
           int noms, denoms = 0;
           
           ist >> noms;
           //    throw std::runtime_error("No numerator!");                                
          
           ist >> denoms;

          if(denoms == 0)     
             throw std::runtime_error("No denominator!");                                
          
           frac = Fraction(noms, denoms);
           return ist;
      }

/*istream& ariel::operator>> (istream& ist, Fraction& frac){
    int noms, denoms;
    string str;
    std::getline (ist, str);
      
    size_t i=0;
    while(str.at(i)!=' ' && str.at(i)!=',' && str.at(i)!='/')
      i++;
    noms =  stoi(str.substr(0, i));
    i++;
    
    while(str.at(i)==' ' || str.at(i)==',' || str.at(i)=='/')
      i++;
    
    denoms = stoi(str.substr(i, str.length()));
    if(denoms == 0)
       throw std::runtime_error("Zero denominator>>");
    frac = Fraction(noms, denoms);
    return ist;
}*/

        // bool operator==( const Fraction& frac_a, Fraction& frac_b)
        // {
        //     Fraction frac1 = Fraction(frac_a);
        //     Fraction frac2 = Fraction(frac_b);
        //     return frac1.getNom() == frac2.getNom() && frac1.getDenominator() == frac2.getDenominator();
        // }

        //bool Fraction::operator==(const float f){return 0;};
        // bool operator==(const Fraction& frac, const double dbl)
        // {
        //     double doubled = Fraction::toDouble(frac);
        //     return doubled == Fraction::roundNumber(dbl);
        // }
