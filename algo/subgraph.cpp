template<typename T> string toString(vector<T> VT) {
   stringstream ss;
   string s;
   for (typename vector<T>::iterator iV = VT.begin(); iV!=VT.end(); iV++) 
    ss << *iV<<".";
   ss >> s;
   return s;
}

class SubGraph {
public:
  int n,e,mgameid;
  map<int,int> subid;
  set< pair<int,int> > SPI;
  set<int> innode;
  SubGraph(int mgid) {
     n = 0;
     e = 0;
     this->mgameid = mgid;
     subid.clear(); SPI.clear(); innode.clear();
     //subgraphid++;
  }
  int getsubid(int x) {
//     cout << "GSid" << x << endl;
     if (subid.find(x)!=subid.end()) return subid[x];
     subid[x] = ++n;
     return subid[x];
  }
  void insertEdge(int x, int y) { //x is innode
     int mx = this->getsubid(x);
     int my = this->getsubid(y);
   //  cout << "within"<<mx<<my<<endl;
     innode.insert(mx);
     if (mx < my) SPI.insert(make_pair(mx,my));
           else   SPI.insert(make_pair(my,mx));
  }
  void tofile() {
     char filename[100];
     sprintf(filename,"%d.sg\0",mgameid);
     if (SPI.empty()) return ;
     FILE *file = fopen(filename,"w");
      int kk;
     fprintf(file,"v %d %d\n",kk = this->n, (int) (SPI.size()) );
     int nnode =0, outnode =0, inedge =0, outedge =0;
     for (int i = 0; i<kk; i++)  {
         if (innode.count(i+1)!=0)
            fprintf(file,"%d %d\n",i,++nnode);
        else 
            fprintf(file,"%d -%d\n",i,++outnode);
     }
     for (set<pair<int,int> > ::iterator iSPI = SPI.begin(); iSPI!=SPI.end(); iSPI++) {
       fprintf(file,"e %d %d ",(iSPI->first)-1,(iSPI->second)-1);
       if (innode.count(iSPI->first) && innode.count(iSPI->second))
         fprintf(file,"%d\n",++inedge); 
       else 
         fprintf(file,"-%d\n",++outedge);
     }
     fclose(file);
  }  
  struct twovalues{
    int A, B;
    twovalues(int _A, int _B) : A(_A),B(_B) {};
    friend ostream & operator <<(ostream & out, twovalues & x) { 
       out << x.A<<"/"<<x.B;
    }
    friend bool operator < (const twovalues &x,const  twovalues &y) {
       if (x.A!=y.A) return (x.A<y.A); else return (x.B<y.B);
    }
  };
  string degree_string_A() {
    //innodecount,(degree_I/I,degree_I/O)*innodes:sorted;(degree_I/O)*outnodes:sorted
    stringstream ss;
    //cout <<"counting"<<endl;
    ss << innode.size() <<";";
//    for (set<int>::iterator innn = innode.begin(); innn!=innode.end(); innn++) cout << *innn <<"-"; cout << endl;
    map<int,int> DII, DIO, DOI;
    for (set<pair<int,int> > ::iterator iSPI = SPI.begin(); iSPI!=SPI.end(); iSPI++) {
       int p1, p2;
       p1 = innode.count(iSPI->first);p2 = innode.count(iSPI->second);
       if (p1 && p2 ) {
         DII[iSPI->first]++; DII[iSPI->second]++; continue;
       }
       if ((p2 ==0) && p1) {DIO[iSPI->first] ++; DOI[iSPI->second]++; }
       else if ((p1==0) && p2)    {DIO[iSPI->second] ++; DOI[iSPI->first]++; }
//       cout << p1 << p2 <<" " << iSPI->first <<" "<<iSPI->second << endl;
    }
    vector<twovalues> TV;
    for (set<int> :: iterator iS = innode.begin(); iS!=innode.end(); iS++)
      TV.push_back(twovalues(DII[*iS],DIO[*iS]));
    sort(TV.begin(),TV.end());
    ss << toString(TV)<<";";
    vector<int> TI;
    for (map<int,int>::iterator iM = DOI.begin(); iM!=DOI.end(); iM++)
      TI.push_back(iM->second);
    sort(TI.begin(),TI.end());
    ss << toString(TI);
    string s;
    ss >> s;
    return s;
  }
  string degree_string_B() {
    //the degree on subgraph
    stringstream ss;
    map<int,int> D;
    for (set<pair<int,int> > ::iterator iSPI = SPI.begin(); iSPI!=SPI.end(); iSPI++) 
       {D[iSPI->second] ++; D[iSPI->first]++; }
    vector<int> TI;
    for (map<int,int>::iterator iM = D.begin(); iM!=D.end(); iM++)
      TI.push_back(iM->second);
    sort(TI.begin(),TI.end());
    ss << toString(TI);
    string s; ss>>s;
    return s;
  }
  
};

