#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Base class Lesson
class Lesson
{
protected:
    string title;
    int duration;   // whole number
    double grade;   // real number
    int difficulty; // between 1 and 3
    string teacher;
    vector<int> ratings; // between 3 and 40

public:
    Lesson(const string &title, int duration, double grade, int difficulty,
           const string &teacher, const vector<int> &ratings)
        : title(title), duration(duration), grade(grade),
          difficulty(difficulty), teacher(teacher), ratings(ratings)
    {

        // Validate difficulty (between 1 and 3)
        if (difficulty < 1 || difficulty > 3)
        {
            throw invalid_argument("Difficulty must be between 1 and 3");
        }

        // Validate ratings (between 3 and 40)
        for (int rating : ratings)
        {
            if (rating < 3 || rating > 40)
            {
                throw invalid_argument("Ratings must be between 3 and 40");
            }
        }
    }

    virtual ~Lesson() {}

    // Getters
    string getTitle() const { return title; }
    int getDuration() const { return duration; }
    double getGrade() const { return grade; }
    int getDifficulty() const { return difficulty; }
    string getTeacher() const { return teacher; }
    vector<int> getRatings() const { return ratings; }

    // Check if lesson has rating in range
    bool hasRatingInRange(int minRating, int maxRating) const
    {
        for (int rating : ratings)
        {
            if (rating >= minRating && rating <= maxRating)
            {
                return true;
            }
        }
        return false;
    }

    // Virtual function for polymorphic output
    virtual void print(ostream &os) const
    {
        os << "Title: " << title << endl;
        os << "Duration: " << duration << " min" << endl;
        os << "Grade: " << grade << endl;
        os << "Difficulty: " << difficulty << endl;
        os << "Teacher: " << teacher << endl;
        os << "Ratings: ";
        for (size_t i = 0; i < ratings.size(); i++)
        {
            os << ratings[i];
            if (i < ratings.size() - 1)
                os << ", ";
        }
        os << endl;
    }

    // Friend function for operator <<
    friend ostream &operator<<(ostream &os, const Lesson &lesson);
};

// Derived class OnlineLesson
class OnlineLesson : public Lesson
{
private:
    string location;

public:
    OnlineLesson(const string &title, int duration, double grade, int difficulty,
                 const string &teacher, const vector<int> &ratings, const string &location)
        : Lesson(title, duration, grade, difficulty, teacher, ratings), location(location) {}

    string getLocation() const { return location; }

    void print(ostream &os) const override
    {
        os << "=== Online Lesson ===" << endl;
        Lesson::print(os);
        os << "Location: " << location << endl;
    }
};

// Derived class LectureLesson
class LectureLesson : public Lesson
{
private:
    string platform;

public:
    LectureLesson(const string &title, int duration, double grade, int difficulty,
                  const string &teacher, const vector<int> &ratings, const string &platform)
        : Lesson(title, duration, grade, difficulty, teacher, ratings), platform(platform) {}

    string getPlatform() const { return platform; }

    void print(ostream &os) const override
    {
        os << "=== Lecture Lesson ===" << endl;
        Lesson::print(os);
        os << "Platform: " << platform << endl;
    }
};

// Operator << overloading
ostream &operator<<(ostream &os, const Lesson &lesson)
{
    lesson.print(os);
    return os;
}

int main()
{
    // Create a collection of lessons
    vector<Lesson *> lessons;

    try
    {
        // Create some OnlineLessons
        lessons.push_back(new OnlineLesson("C++ Basics", 60, 5.5, 2, "Prof. Ivan", {5, 8, 10, 4}, "Zoom"));
        lessons.push_back(new OnlineLesson("OOP Concepts", 90, 5.8, 3, "Prof. Maria", {3, 4, 5, 12}, "Teams"));
        lessons.push_back(new OnlineLesson("Data Structures", 75, 5.2, 2, "Prof. Peter", {15, 20, 25}, "Google Meet"));

        // Create some LectureLessons
        lessons.push_back(new LectureLesson("Advanced C++", 120, 6.0, 3, "Prof. George", {30, 35, 40}, "Auditorium A"));
        lessons.push_back(new LectureLesson("Algorithms", 100, 5.7, 2, "Prof. Anna", {4, 5, 6}, "Room 205"));
        lessons.push_back(new LectureLesson("Software Engineering", 80, 5.9, 3, "Prof. John", {18, 22, 28}, "Hall B"));

        cout << "All Lessons:" << endl;
        cout << "============================================" << endl
             << endl;

        for (const auto &lesson : lessons)
        {
            cout << *lesson << endl;
        }

        // Search for lessons with ratings in range [3, 5]
        int minRating = 3;
        int maxRating = 5;

        vector<Lesson *> lessonsInRange;
        int onlineLessonsInRange = 0;
        int totalOnlineLessons = 0;

        cout << "\n============================================" << endl;
        cout << "Lessons with ratings between " << minRating << " and " << maxRating << ":" << endl;
        cout << "============================================" << endl
             << endl;

        for (auto lesson : lessons)
        {
            // Check if it's an OnlineLesson
            OnlineLesson *onlineLesson = dynamic_cast<OnlineLesson *>(lesson);
            if (onlineLesson)
            {
                totalOnlineLessons++;
            }

            // Check if lesson has rating in range
            if (lesson->hasRatingInRange(minRating, maxRating))
            {
                lessonsInRange.push_back(lesson);
                cout << *lesson << endl;

                // If it's an online lesson with rating in range
                if (onlineLesson)
                {
                    onlineLessonsInRange++;
                }
            }
        }

        // Calculate percentage
        if (totalOnlineLessons > 0)
        {
            double percentage = (static_cast<double>(onlineLessonsInRange) / totalOnlineLessons) * 100.0;
            cout << "============================================" << endl;
            cout << "Statistics:" << endl;
            cout << "Total online lessons: " << totalOnlineLessons << endl;
            cout << "Online lessons with ratings in range [" << minRating << ", " << maxRating << "]: "
                 << onlineLessonsInRange << endl;
            cout << "Percentage: " << percentage << "%" << endl;
        }
        else
        {
            cout << "No online lessons found." << endl;
        }

        // Clean up memory
        for (auto lesson : lessons)
        {
            delete lesson;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        // Clean up memory in case of exception
        for (auto lesson : lessons)
        {
            delete lesson;
        }
        return 1;
    }

    return 0;
}
