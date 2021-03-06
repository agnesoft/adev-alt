#ifdef _MSC_VER
export module abuild_test_utilities : test_cache;

export import "rapidjson.hpp";
export import<astl.hpp>;
#endif

export class TestCache
{
public:
    TestCache()
    {
        removeFile();
    }

    TestCache(const std::string &data)
    {
        std::filesystem::create_directory(mFilePath.parent_path());
        std::ofstream file{mFilePath};
        std::string buffer = jsonFormat(data);
        file.write(buffer.c_str(), buffer.size());
    }

    TestCache(TestCache &other) = delete;
    TestCache(TestCache &&other) noexcept = default;

    ~TestCache()
    {
        try
        {
            try
            {
                removeFile();
            }
            catch (std::exception &e)
            {
                std::cout << "Failed to remove file '" << mFilePath << ": " << e.what() << '\n';
            }
        }
        catch (...)
        {
        }
    }

    [[nodiscard]] auto content() const -> std::string
    {
        std::ifstream file{mFilePath};
        std::string data;

        file.seekg(0, std::ios::end);
        data.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        data.assign(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});

        return data;
    }

    [[nodiscard]] auto file() const noexcept -> const std::filesystem::path &
    {
        return mFilePath;
    }

    [[nodiscard]] static auto jsonFormat(const std::string &data) -> std::string
    {
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{buffer};
        rapidjson::Document doc;
        doc.Parse(data.c_str());
        doc.Accept(writer);
        return std::string(buffer.GetString(), buffer.GetSize());
    }

    [[nodiscard]] auto exists() -> bool
    {
        return std::filesystem::exists(mFilePath);
    }

    auto operator=(TestCache &other) -> TestCache & = delete;
    auto operator=(TestCache &&other) noexcept -> TestCache & = default;

private:
    auto removeFile() -> void
    {
        std::filesystem::remove(mFilePath);
    }

    std::filesystem::path mFilePath = std::filesystem::current_path() / "build_test" / ".abuild";
};