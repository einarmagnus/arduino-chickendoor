// returns millis from t1 to t2, handles the ~50 day wrap.
unsigned long time_diff(unsigned long t1, unsigned long t2) {
    if (t1 <= t2) {
       return t2 - t1;
    } else {
      //time has overflowed, happens every 50 days
      return t2 + (((unsigned long)-1l) - t1);
    }
};
