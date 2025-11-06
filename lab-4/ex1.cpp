// media_collection_single.cpp
#include <iostream>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <sstream>
#include <iomanip>

enum class ContentType
{
    MUSIC,
    MOVIE,
    GAME
};
enum class MediaFormat
{
    CD,
    DVD,
    VIDEO,
    DIGITAL
};

struct Date
{
    int year{1970}, month{1}, day{1};
    std::string str() const
    {
        std::ostringstream os;
        os << std::setfill('0')
           << std::setw(2) << day << "."
           << std::setw(2) << month << "."
           << year;
        return os.str();
    }
};

class Item
{
public:
    Item(const Item &) = delete;
    Item &operator=(const Item &) = delete;
    Item(Item &&) = delete;
    Item &operator=(Item &&) = delete;
    virtual ~Item() { usedIds.erase(itemId_); }

    // getters
    ContentType getContentType() const { return contentType_; }
    Date getDatePurchased() const { return datePurchased_; }
    const std::string &getItemId() const { return itemId_; }
    MediaFormat getMediaFormat() const { return mediaFormat_; }
    int getNumberOfItems() const { return numberOfItems_; }
    double getPrice() const { return price_; }
    const std::string &getTitle() const { return title_; }

    // exact message format
    virtual std::string toString() const
    {
        std::ostringstream os;
        os << typeBgName() << " с заглавие \"" << title_
           << "\" е била купена на цена " << priceAsString()
           << " на дата " << datePurchased_.str() << ".";
        return os.str();
    }

protected:
    Item(ContentType contentType,
         Date datePurchased,
         std::string itemId,
         MediaFormat mediaFormat,
         int numberOfItems,
         double price,
         std::string title)
        : contentType_(contentType),
          datePurchased_(datePurchased),
          mediaFormat_(mediaFormat),
          numberOfItems_(numberOfItems),
          price_(price),
          title_(std::move(title))
    {

        if (itemId.empty())
            throw std::invalid_argument("itemId е задължителен.");
        if (numberOfItems_ <= 0)
            throw std::invalid_argument("numberOfItems трябва да е > 0.");

        if (!usedIds.insert(itemId).second)
        {
            throw std::invalid_argument("Дублирано itemId: " + itemId);
        }
        itemId_ = std::move(itemId);
    }

    static std::string contentTypeToBg(ContentType t)
    {
        switch (t)
        {
        case ContentType::MUSIC:
            return "Музика";
        case ContentType::MOVIE:
            return "Филм";
        case ContentType::GAME:
            return "Игра";
        }
        return "Медия";
    }
    std::string typeBgName() const { return contentTypeToBg(contentType_); }

    std::string priceAsString() const
    {
        std::ostringstream os;
        os << std::fixed << std::setprecision(2) << price_;
        return os.str();
    }

private:
    inline static std::unordered_set<std::string> usedIds;

    ContentType contentType_;
    Date datePurchased_;
    std::string itemId_;
    MediaFormat mediaFormat_;
    int numberOfItems_;
    double price_;
    std::string title_;
};

// ----- Movie -----
class Movie : public Item
{
public:
    Movie(std::string itemId, std::string title, double price, Date datePurchased,
          MediaFormat mediaFormat, int numberOfItems, std::string rating)
        : Item(ContentType::MOVIE, datePurchased, std::move(itemId), mediaFormat,
               numberOfItems, price, std::move(title)),
          rating_(std::move(rating)) {}

    const std::string &getRating() const { return rating_; }
    std::string playOnDVD() const { return "Пуска се филм \"" + getTitle() + "\" от DVD..."; }
    std::string playOnVideo() const { return "Пуска се филм \"" + getTitle() + "\" от видео файл..."; }

private:
    std::string rating_; // G, PG-13, R...
};

// ----- Game -----
class Game : public Item
{
public:
    Game(std::string itemId, std::string title, double price, Date datePurchased,
         MediaFormat mediaFormat, int numberOfItems, int difficultyLevel, std::string mfg)
        : Item(ContentType::GAME, datePurchased, std::move(itemId), mediaFormat,
               numberOfItems, price, std::move(title)),
          difficultyLevel_(difficultyLevel), mfg_(std::move(mfg)) {}

    int getDifficultyLevel() const { return difficultyLevel_; }
    const std::string &getMfg() const { return mfg_; }
    std::string playOnCD() const { return "Стартира игра \"" + getTitle() + "\" от CD..."; }

private:
    int difficultyLevel_;
    std::string mfg_;
};

// ----- Music -----
class Music : public Item
{
public:
    Music(std::string itemId, std::string title, double price, Date datePurchased,
          MediaFormat mediaFormat, int numberOfItems, std::string bandOrArtist)
        : Item(ContentType::MUSIC, datePurchased, std::move(itemId), mediaFormat,
               numberOfItems, price, std::move(title)),
          bandOrArtist_(std::move(bandOrArtist)) {}

    const std::string &getBandOrArtist() const { return bandOrArtist_; }
    std::string playOnCD() const
    {
        return "Възпроизвежда се \"" + getTitle() + "\" на " + bandOrArtist_ + " от CD...";
    }

private:
    std::string bandOrArtist_;
};

// ----- Demo -----
int main()
{
    try
    {
        Movie m{"M001", "The Matrix", 19.99, {2024, 3, 15}, MediaFormat::DVD, 1, "R"};
        Music mu{"MU123", "Greatest Hits", 9.99, {2025, 1, 10}, MediaFormat::CD, 1, "Queen"};
        Game g{"G77", "StarCraft", 29.00, {1999, 7, 1}, MediaFormat::CD, 2, 7, "Blizzard"};

        std::cout << m.toString() << "\n";
        std::cout << mu.toString() << "\n";
        std::cout << g.toString() << "\n\n";

        std::cout << m.playOnDVD() << "\n";
        std::cout << mu.playOnCD() << "\n";
        std::cout << g.playOnCD() << "\n";

        // Uncomment to test unique ID enforcement:
        // Movie dup{"M001", "Another", 10.0, {2024,1,1}, MediaFormat::DVD, 1, "PG"};
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Грешка: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
