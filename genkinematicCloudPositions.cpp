// genKCP
// generate openFoam file kinematicCloudPositions
// 20201217 144000

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<cmath>

enum class mc : int // message code
{ start = 0, end = 1, errorNumArgs = 2
};

std::map<mc,std::string> msg; // standard messages

class Point //-----------------------------------------------------------------
{ public:  
    Point()=default;
    ~Point()=default;
    void x(const float x) { x_ = x;}
    void y(const float y) { y_ = y;}
    void z(const float z) { z_ = z;}
    void xyz(const float ax, const float ay, const float az)
    {   x(ax); 
        y(ay);
        z(az);
    }
    const float x() { return x_;}
    const float y() { return y_;}
    const float z() { return z_;}
  private:
    float x_;
    float y_;
    float z_;
};//class Point //--------------------------------------------------------------


void out(std::map<mc,std::string> msg, mc mCode)
{   std::cout << msg[mCode];
    return;
}

void prgInit()
{   msg[mc::start]="\ngenKCP -- generate OpenFoam file kinematicCloudPositions\nVersion 0.1 -- 2020.12.18-09.19.00\n\n";
    msg[mc::end]="\nExecution ended successfully.\n\n";
    msg[mc::errorNumArgs]="\nError: wrong number of arguments. Expected 13.\n\n";
}

int main(int argc, char* argv[]) //=============================================
{   prgInit();
    out(msg, mc::start);
    Point point;
    std::cout << "process...\n";
//    point.xyz(2.3,3.4,4.5);
//    std::cout << point.x()<<"\n";
    if (argc != 14)
    {   out(msg, mc::errorNumArgs);
        return 2;
    }
    float n=std::stof(argv[1]); //total number of points
    float nx=std::stof(argv[2]); //number of x divisions
    float xi=std::stof(argv[3]); //initial x
    float xf=std::stof(argv[4]); //final x
    float fx=std::stof(argv[5]); //factor x
    float Dx=xf-xi;
    float dx=Dx/(nx-1);
    float ny=std::stof(argv[6]);
    float yi=std::stof(argv[7]);
    float yf=std::stof(argv[8]);
    float fy=std::stof(argv[9]); //factor y
    float Dy=yf-yi;
    float dy=Dy/(ny-1);
    float nz=std::stof(argv[10]);
    float zi=std::stof(argv[11]);
    float zf=std::stof(argv[12]);
    float fz=std::stof(argv[13]); //factor z
    float Dz=zf-zi;
    float dz=Dz/(nz-1);
    float xx,yy,zz;
    float f;

    std::cout << "nx="<<nx<<", ny="<<ny<<", nz="<<nz<<".\n";
    for(int iz=0; iz<nz; ++iz)
    {   zz=zi+iz*dz;
        for(int iy=0; iy<ny; ++iy)
        {   yy=yi+iy*dy;
            for(int ix=0; ix<nx; ++ix)
            {   xx=xi+ix*dx;
                f=std::exp(fx*std::pow(xx,2))+
                  std::exp(fy*std::pow(yy,2))+
                  std::exp(fz*std::pow(zz,2));
                point.xyz(xx,yy,zz);
                std::cout << "Point (ix="<<ix<<", iy="<<iy<<", iz="<<iz
                          << ") coordinates = "
                          <<"(x=" <<point.x()
                          <<", y="<<point.y()
                          <<", z="<<point.z()
                          <<"), factor f="<<f<<".\n";
            }
        }
    }
    out(msg, mc::end);
    return 0;
}//int main(int argc, char* argv[]) //=========================================

