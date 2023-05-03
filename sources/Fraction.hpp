#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <numeric>
#include<cmath>

using namespace std;
 namespace ariel{
class Fraction
{
   int nom ;//numerator
   int denom ;//denominator
public:
   //int getNumerator();
   //int getDenominator();
   int const getNumerator();
   int const getDenominator();
    //Constructors:
    Fraction();
    Fraction(int new_n, int new_d);
    Fraction(double dbl)
    {
      Fraction temp = Fraction::toFraction(dbl);
      nom = temp.getNumerator();
      denom = temp.getDenominator();
    }
    //

// Conversion operator from Fraction to double
    // operator double() const {
    //     return Fraction::roundNumber(static_cast<double>(nom) / static_cast<double>(denom));
    // }
    void simplify();
    static int gcd(int aaa, int bbb); //Greatest Common Divider.
    int lcm(int aaa, int bbb); //Least Common Multiple.
    static double roundNumber(double numberToRound /*The number to round*/)  //roundin numbers to any number of digits after
        {                                                     //the decimal point.
           const int TEN_ = 10;
           const int DECIMAL_PLACES_=3;
           const double ONE_HALF_ = 0.5;
           double multiplyer = pow(TEN_, DECIMAL_PLACES_);
           double shifted = numberToRound * multiplyer;
           if(fabs(fmod(shifted, 1)) >= ONE_HALF_)
              {
                shifted = (shifted>0) ? ceil(shifted) : floor(shifted);
              }   //based on the sign of the number
           else                                                         // we decide to floor or ceil.
              {
                shifted = (shifted>0) ? floor(shifted) : ceil(shifted);        
              }
           return shifted/multiplyer;
        }
    static double toDouble(Fraction frac){
        //cout<<"doubled("<<frac<<") to"<<(1.0*frac.nom)/frac.denom<<endl;
        if(frac.getDenominator() == 0)
          {
            throw std::invalid_argument("Division by zero!");
          }
        return roundNumber((1.0*frac.nom)/frac.denom);
    }
    static Fraction toFraction(double dbl)
    {
        const int TEN_ = 10;
        static int MAX_DIGITS = 3;
        dbl = Fraction::roundNumber(dbl);
        int numinator = static_cast<int>(round(dbl * pow(TEN_, MAX_DIGITS)));
        int dominator = static_cast<int>(pow(TEN_, MAX_DIGITS));
        int commonDivsor = Fraction::gcd(numinator, dominator);
        numinator /= commonDivsor;
        dominator /= commonDivsor;
        return Fraction(numinator, dominator);
    }
    /*Overloaded Arithmetic Aperators:*/

    //addition
        Fraction operator+(Fraction) ;        
        double operator+(double);
        //Fraction operator+(const double);                
        friend double operator+(double dbl,  Fraction frac)
        {
            return Fraction::roundNumber(Fraction::toDouble(frac)+dbl);  //*1.0 for casting to double          
        }
        
        //subtraction
        Fraction operator-(Fraction);        
        double operator-(double);
        friend double operator-(double dbl, const Fraction& frac) {
            return roundNumber(dbl-((frac.nom*1.0)/frac.denom));  //*1.0 for casting to double          
        }
       // friend Fraction operator-(Fraction frac1, Fraction frac2){
         //   return Fraction(Fraction::toDouble(frac1)-Fraction::toDouble(frac2));
        //}
        
        //multiplication
        Fraction operator*(const Fraction&);
       // friend Fraction operator*(Fraction frac1, Fraction frac2){
         //  return Fraction(frac1.getNumerator()*frac2.getNumerator(), frac1.getDenominator()*frac2.getDenominator());
        //  }
        friend Fraction operator*( double dbl, Fraction frac);
        //Fraction operator*(const float);
        Fraction operator*(double);
        
        //devision
        Fraction operator/(Fraction);        
        Fraction operator/(double);
        friend Fraction operator/(double dbl, Fraction frac){
            return Fraction::toFraction(dbl) / frac;
        }
    
        
        //bool operator==(Fraction& frac1) const;
        friend bool operator==(const Fraction& frac1,const Fraction& frac2){
            return frac1.nom == frac2.nom && frac1.denom == frac2.denom;
        }
        bool operator==(double dbl) const;
        friend bool operator==(double dbl, Fraction frac){
            return dbl == roundNumber(toDouble(frac));
        }
        

        friend bool operator!=(const Fraction& frac1,const Fraction& frac2){
            return frac1.nom != frac2.nom || frac1.denom != frac2.denom;
        }

        bool operator!=(Fraction& frac1) const{
             return this->nom != frac1.nom || this->denom != frac1.denom;
        }
        bool operator!=(double& dbl) const{
             return toDouble(*this) != roundNumber(dbl);
        }

        friend bool operator!=(double dbl, Fraction frac){
            return Fraction::roundNumber(dbl) != Fraction::toDouble(frac);
        }

        // (>,<,>=,<=)
        bool operator>(const Fraction& frac) const;
        friend bool operator>(const double dbl, const Fraction& frac)
        {
            return Fraction::toDouble(frac) < Fraction::roundNumber(dbl);
        }
        friend bool operator>(const Fraction& frac,  const double& dbl) 
        {            
            return Fraction::toDouble(frac) > Fraction::roundNumber(dbl);
        }
        bool operator>(double dbl)
        {
            return Fraction::toDouble(*this) > dbl;
        }

               
        friend bool operator<(const double& dbl, const Fraction& frac)
        {
            return Fraction::toDouble(frac) > Fraction::roundNumber(dbl);
        }
        friend bool operator<(const Fraction& frac, const double& dbl)
        {
               return Fraction::toDouble(frac) < Fraction::roundNumber(dbl);
        }
        bool operator<(Fraction frac) const;

        bool operator>=(Fraction frac) const;        
        bool operator>=(double dbl);
        friend bool operator>=(double dbl, Fraction frac){
            return dbl>=Fraction::toDouble(frac);
        }

        bool operator<=(Fraction frac) const;
        bool operator<=(double dbl);
        friend bool operator<=(double dbl, Fraction frac){
            return dbl<=Fraction::toDouble(frac);
        }
        // friend bool operator<=(Fraction frac1, Fraction frac2){
        //     return Fraction::toDouble(frac1)<=Fraction::toDouble(frac2);
        // }


        Fraction& operator++();           //pre increment
        Fraction operator++(int); //post increment
        Fraction& operator--();           //pre decrement
        Fraction operator--(int); //post decrement
       

   
    
    friend ostream& operator<< (ostream& ost, Fraction frac);
    friend istream& operator>> (istream& ist, Fraction& frac);
}; 
} 

#endif