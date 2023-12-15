namespace rapidjson
{
    // StringStream

    //! Read-Write string stream.
    /*! \note implements Stream concept
     */
    template <typename Encoding>
    struct ReadWriteStringStream
    {
        typedef typename Encoding::Ch Ch;

        ReadWriteStringStream(Ch* src) : src_(src), head_(src) {}

        Ch Peek() const { return *src_; }
        Ch Take() { return *src_++; }
        size_t Tell() const { return static_cast<size_t>(src_ - head_); }

        Ch* PutBegin()
        {
            RAPIDJSON_ASSERT(false);
            return 0;
        }
        void Put(Ch c) { *src_++ = c; }
        void Flush() { RAPIDJSON_ASSERT(false); }
        size_t PutEnd(Ch*)
        {
            RAPIDJSON_ASSERT(false);
            return 0;
        }

        Ch* src_;        //!< Current read position.
        const Ch* head_; //!< Original head of the string.
    };
}