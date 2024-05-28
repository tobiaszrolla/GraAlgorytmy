#ifndef PIONLOG_H_
#define PIONLOG_H_
class PionLog
{
    private:
        // odpowiada za zatrzymanie ruchów
        bool lock;
        //pozycja na x
        int x;
        //pozycja na y
        int y;
    public:
    /*Konst/Dest*/
    PionLog(int x, int y, bool lock): x{x},y{y},lock{lock}
    {
    }
    ~PionLog(){};
    /*Getter*/
    int get_x() const
        {
            return x;
        }
    int get_y() const
        {
            return y;
        }
    bool get_lock() const
    {
        return lock;
    }
    /*Setter*/
    void set_pos(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
    void set_lock(bool lock)
        {
            this->lock = lock;
        }
};
#endif /*PIONLOG_H_*/