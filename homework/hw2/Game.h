class Game {
    public:
        // constructor
        Game();

        // accessors
        Date getDate() const;
        TeamSummary getVisitorSummary() const;
        TeamSummary getHomeSummary() const;

        // modifiers
        void setDate(const Date date);
        void setVisitorSummary(const TeamSummary visitorSummary);
        void setHomeSummary(const TeamSummary homeSummary);

    private:
        Date date;
        TeamSummary visitorSummary;
        TeamSummary homeSummary;
};
