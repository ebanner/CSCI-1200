class TeamSummary {
    public:
        // constructor
        TeamSummary();

        // accessors
        int getQ1() const;
        int getQ2() const;
        int getQ3() const;
        int getQ4() const;
        int getOT() const;
        int[] getQuarters() const;
        int getScore() const;

        // modifiers
        int setQ1(const int Q1);
        int setQ2(const int Q2);
        int setQ3(const int Q3);
        int setQ4(const int Q4);
        int setOT(const int OT);
        int[] setQuarters(const int &quarters[]);
        int setScore(const int score);
        
    private:
        String team;
        int quarters[5]; // haha, not really `quarters'
        int score;
};
