#ifndef MYUTILITIES_H
#define MYUTILITIES_H

bool isNumber(QString a){
    for(int i=0;i<a.size();i++){
        if(a[i]<'0' || a[i]>'9')return false;
    }
    return true;
}

bool myorder(pair<QString,pair<int,int>> a,pair<QString,pair<int,int>> b){
    return (a.second).first < (b.second).first;
}

#endif // MYUTILITIES_H
