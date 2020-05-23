#ifndef ACORE_VARIANT_HPP
#define ACORE_VARIANT_HPP

#include "DataStream.hpp"

#include <string>

namespace acore
{
//! The Variant provides open union functionality
//! for common types.
//!
//! The Variant class can store any type as long
//! as it provides DataStream streaming operators.
//! Storing the value in a variant is done in its
//! constructor while restoring is done via the
//! value() method. The isValid() method can be
//! used to check if the Variant holds a value.
//!
//! The Variant is not very suitable for small data
//! types due to significant overhead of its type
//! erasure mechanism (serialization).
class Variant
{
public:
    //! Constructs an empty Variant.
    Variant() = default;

    //! Constructs a Variant from \a value.
    template<typename T>
    explicit constexpr Variant(const T &value)
    {
        mStream << value;
    }

    // template<>
    // explicit Variant(const std::string &value) :
    //     mStream{std::vector<char>(value.begin(), value.end())}
    // {
    // }

    // template<>
    // explicit Variant(const std::vector<char> &value) :
    //     mStream{value}
    // {
    // }

    //! Returns \c true if the Variant holds a
    //! value or \c false otherwise.
    [[nodiscard]] auto isValid() const noexcept -> bool
    {
        return mStream.buffer().size() != 0;
    }

    //! Converts variant to the value of type T from.
    //! If the operation fails (e.g. Variant is empty
    //! or of different type) a default constructed
    //! T is returned.
    template<typename T>
    [[nodiscard]] auto value() const -> T
    {
        T val{};

        if (mStream.buffer().size() > 0)
        {
            mStream.reset();

            try
            {
                mStream >> val;
            }
            catch ([[maybe_unused]] acore::Exception &e)
            {
            }
        }

        return val;
    }

    // template<>
    // [[nodiscard]] auto value() const -> const std::vector<char> &
    // {
    //     return mStream.buffer().data();
    // }

    // template<>
    // [[nodiscard]] auto value() const -> std::string
    // {
    //     return std::string(mStream.buffer().data().begin(), mStream.buffer().data().end());
    // }

    // template<>
    // [[nodiscard]] auto value() const -> std::vector<char>
    // {
    //     return mStream.buffer().data();
    // }

    // template<>
    // [[nodiscard]] auto value() const -> Variant
    // {
    //     return *this;
    // }

private:
    //! \relates Variant
    //! Returns \c true if the \a left holds the same
    //! value as does the \a right.
    friend auto operator==(const Variant &left, const Variant &right) noexcept -> bool
    {
        return left.mStream.buffer().data() == right.mStream.buffer().data();
    }

    //! \relates Variant
    //! Returns \c true if the \a left holds different
    //! value than the \a right.
    friend auto operator!=(const Variant &left, const Variant &right) noexcept -> bool
    {
        return !(left == right);
    }

    //! \relates Variant
    //! Serializes the \a value into the \a stream
    //! and returns the \a stream.
    template<typename Buffer>
    friend constexpr auto operator<<(DataStreamBase<Buffer> &stream, const Variant &value) -> DataStreamBase<Buffer> &
    {
        return stream << value.mStream.buffer().data();
    }

    //! \relates Variant
    //! Deserializes the \a value from the \a stream
    //! and returns the \a stream.
    template<typename Buffer>
    friend constexpr auto operator>>(DataStreamBase<Buffer> &stream, Variant &value) -> DataStreamBase<Buffer> &
    {
        return stream >> value.mStream.buffer().data();
    }

    mutable DataStream mStream;
};

#endif
