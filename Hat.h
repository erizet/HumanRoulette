#ifndef hat_h
#define hat_h

class Hat {
public:
   virtual void SetColor(boolean R, boolean G, boolean B) { return; }
   char sendString[13];
};


class HatA : public Hat {
public:
   HatA();
   virtual void SetColor(boolean R, boolean G, boolean B);
};

class HatB : public Hat {
public:
   HatB();
   virtual void SetColor(boolean R, boolean G, boolean B);
};

class HatC : public Hat {
public:
   HatC();
   virtual void SetColor(boolean R, boolean G, boolean B);
};

class HatD : public Hat {
public:
   HatD();
   virtual void SetColor(boolean R, boolean G, boolean B);
};


#endif
