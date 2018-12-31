#ifndef E57FORMATIMPL_H_INCLUDED
#define E57FORMATIMPL_H_INCLUDED

/*
 * E57FormatImpl.h - private implementation header of E57 format implementation.
 *
 * Copyright 2009 - 2010 Kevin Ackley (kackley@gwi.net)
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "Packet.h"
#include "StructureNodeImpl.h"

namespace e57 {

class E57XmlParser;
class Decoder;
class Encoder;

//================================================================

class VectorNodeImpl : public StructureNodeImpl {
public:
    explicit VectorNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile, bool allowHeteroChildren);
             ~VectorNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        allowHeteroChildren() const;

    void        set(int64_t index, std::shared_ptr<NodeImpl> ni) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

#ifdef E57_DEBUG
    void    dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    bool allowHeteroChildren_;
};

//================================================================

class CompressedVectorNodeImpl : public NodeImpl {
public:
    CompressedVectorNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile);
    ~CompressedVectorNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;
    void        setAttachedRecursive() override;

    void                setPrototype(const std::shared_ptr<NodeImpl>& prototype);
    std::shared_ptr<NodeImpl> getPrototype();
    void                setCodecs(const std::shared_ptr<VectorNodeImpl> &codecs);
    std::shared_ptr<VectorNodeImpl> getCodecs();

    virtual int64_t     childCount();

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

    /// Iterator constructors
    std::shared_ptr<CompressedVectorWriterImpl> writer(std::vector<SourceDestBuffer> sbufs);
    std::shared_ptr<CompressedVectorReaderImpl> reader(std::vector<SourceDestBuffer> dbufs);

    int64_t             getRecordCount()                        {return(recordCount_);}
    uint64_t            getBinarySectionLogicalStart()          {return(binarySectionLogicalStart_);}
    void                setRecordCount(int64_t recordCount)    {recordCount_ = recordCount;}
    void                setBinarySectionLogicalStart(uint64_t binarySectionLogicalStart)
                                                                {binarySectionLogicalStart_ = binarySectionLogicalStart;}

#ifdef E57_DEBUG
    void                dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    friend class CompressedVectorReaderImpl;

    std::shared_ptr<NodeImpl> prototype_;
    std::shared_ptr<VectorNodeImpl> codecs_;

    int64_t                     recordCount_;
    uint64_t                    binarySectionLogicalStart_;
};

class IntegerNodeImpl : public NodeImpl {
public:
    IntegerNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile, int64_t value = 0, int64_t minimum = 0, int64_t maximum = 0);
    ~IntegerNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;

    int64_t             value();
    int64_t             minimum();
    int64_t             maximum();

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

#ifdef E57_DEBUG
    void        dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    int64_t             value_;
    int64_t             minimum_;
    int64_t             maximum_;
};

class ScaledIntegerNodeImpl : public NodeImpl {
public:
    ScaledIntegerNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile,
                          int64_t value = 0, int64_t minimum = 0, int64_t maximum = 0,
                          double scale = 1.0, double offset = 0.0);

    ScaledIntegerNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile,
                          double scaledValue = 0., double scaledMinimum = 0., double scaledMaximum = 0.,
                          double scale = 1.0, double offset = 0.0);

    ~ScaledIntegerNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;

    int64_t             rawValue();
    double              scaledValue();
    int64_t             minimum();
    double              scaledMinimum();
    int64_t             maximum();
    double              scaledMaximum();
    double              scale();
    double              offset();

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;


#ifdef E57_DEBUG
    void    dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    int64_t             value_;
    int64_t             minimum_;
    int64_t             maximum_;
    double              scale_;
    double              offset_;
};

class FloatNodeImpl : public NodeImpl {
public:
    FloatNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile,
                  double value = 0, FloatPrecision precision = E57_DOUBLE,
                  double minimum = E57_DOUBLE_MIN, double  maximum = E57_DOUBLE_MAX);
    ~FloatNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;

    double              value() const;
    FloatPrecision      precision() const;
    double              minimum() const;
    double              maximum() const;

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

#ifdef E57_DEBUG
    void    dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    double              value_;
    FloatPrecision      precision_;
    double              minimum_;
    double              maximum_;
};

class StringNodeImpl : public NodeImpl {
public:
    explicit StringNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile, const ustring &value = "");
    ~StringNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;

    ustring             value();

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

#ifdef E57_DEBUG
    void    dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    ustring             value_;
};

class BlobNodeImpl : public NodeImpl {
public:
    BlobNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile, int64_t byteCount);
    BlobNodeImpl(std::weak_ptr<ImageFileImpl> destImageFile, int64_t fileOffset, int64_t length);
    ~BlobNodeImpl() override = default;

    NodeType    type() const override;
    bool        isTypeEquivalent(std::shared_ptr<NodeImpl> ni) override;
    bool        isDefined(const ustring& pathName) override;

    int64_t             byteCount();
    void                read(uint8_t* buf, int64_t start, size_t count);
    void                write(uint8_t* buf, int64_t start, size_t count);

    void        checkLeavesInSet(const std::set<ustring>& pathNames, std::shared_ptr<NodeImpl> origin) override;

    void        writeXml(std::shared_ptr<ImageFileImpl> imf, CheckedFile& cf, int indent, const char* forcedFieldName=nullptr) override;

#ifdef E57_DEBUG
    void    dump(int indent = 0, std::ostream& os = std::cout) const override;
#endif

protected:
    uint64_t            blobLogicalLength_;
    uint64_t            binarySectionLogicalStart_;
    uint64_t            binarySectionLogicalLength_;
};

//================================================================

struct DecodeChannel {
    SourceDestBuffer    dbuf; //??? for now, one input per channel
    std::shared_ptr<Decoder> decoder;
    unsigned            bytestreamNumber;
    uint64_t            maxRecordCount;
    uint64_t            currentPacketLogicalOffset;
    size_t              currentBytestreamBufferIndex;
    size_t              currentBytestreamBufferLength;
    bool                inputFinished;

                        DecodeChannel(SourceDestBuffer dbuf_arg, std::shared_ptr<Decoder> decoder_arg, unsigned bytestreamNumber_arg, uint64_t maxRecordCount_arg);

    bool                isOutputBlocked() const;
    bool                isInputBlocked() const;   /// has exhausted data in the current packet
#ifdef E57_DEBUG
    void        dump(int indent = 0, std::ostream& os = std::cout);
#endif
};

//================================================================

class CompressedVectorReaderImpl {
public:
                CompressedVectorReaderImpl(std::shared_ptr<CompressedVectorNodeImpl> ni, std::vector<SourceDestBuffer>& dbufs);
                ~CompressedVectorReaderImpl();
    unsigned    read();
    unsigned    read(std::vector<SourceDestBuffer>& dbufs);
    void        seek(uint64_t recordNumber);
    bool        isOpen() const;
    std::shared_ptr<CompressedVectorNodeImpl> compressedVectorNode() const;
    void        close();

#ifdef E57_DEBUG
    void        dump(int indent = 0, std::ostream& os = std::cout);
#endif

protected:
    void        checkImageFileOpen(const char* srcFileName, int srcLineNumber, const char* srcFunctionName) const;
    void        checkReaderOpen(const char* srcFileName, int srcLineNumber, const char* srcFunctionName) const;
    void        setBuffers(std::vector<SourceDestBuffer>& dbufs); //???needed?
    uint64_t    earliestPacketNeededForInput() const;
    void        feedPacketToDecoders(uint64_t currentPacketLogicalOffset);
    uint64_t    findNextDataPacket(uint64_t nextPacketLogicalOffset);

    //??? no default ctor, copy, assignment?

    bool                                        isOpen_;
    std::vector<SourceDestBuffer>               dbufs_;
    std::shared_ptr<CompressedVectorNodeImpl> cVector_;
    std::shared_ptr<NodeImpl>                 proto_;
    std::vector<DecodeChannel>                  channels_;
    PacketReadCache*                            cache_;

    uint64_t    recordCount_;                   /// number of records written so far
    uint64_t    maxRecordCount_;
    uint64_t    sectionEndLogicalOffset_;
};

//================================================================

class CompressedVectorWriterImpl {
public:
                CompressedVectorWriterImpl(std::shared_ptr<CompressedVectorNodeImpl> ni, std::vector<SourceDestBuffer>& sbufs);
                ~CompressedVectorWriterImpl();
    void        write(const size_t requestedRecordCount);
    void        write(std::vector<SourceDestBuffer>& sbufs, const size_t requestedRecordCount);
    bool        isOpen() const;
    std::shared_ptr<CompressedVectorNodeImpl> compressedVectorNode() const;
    void        close();

#ifdef E57_DEBUG
    void        dump(int indent = 0, std::ostream& os = std::cout);
#endif

protected:
    void        checkImageFileOpen(const char* srcFileName, int srcLineNumber, const char* srcFunctionName) const;
    void        checkWriterOpen(const char* srcFileName, int srcLineNumber, const char* srcFunctionName) const;
    void        setBuffers(std::vector<SourceDestBuffer>& sbufs); //???needed?
    size_t      totalOutputAvailable() const;
    size_t      currentPacketSize() const;
    uint64_t    packetWrite();
    void        flush();

    //??? no default ctor, copy, assignment?

    std::vector<SourceDestBuffer>               sbufs_;
    std::shared_ptr<CompressedVectorNodeImpl> cVector_;
    std::shared_ptr<NodeImpl>                 proto_;

    std::vector<std::shared_ptr<Encoder> >  bytestreams_;
    DataPacket              dataPacket_;

    bool                    isOpen_;
    uint64_t                sectionHeaderLogicalStart_;     /// start of CompressedVector binary section
    uint64_t                sectionLogicalLength_;          /// total length of CompressedVector binary section
    uint64_t                dataPhysicalOffset_;            /// start of first data packet
    uint64_t                topIndexPhysicalOffset_;        /// top level index packet
    uint64_t                recordCount_;                   /// number of records written so far
    uint64_t                dataPacketsCount_;              /// number of data packets written so far
    uint64_t                indexPacketsCount_;             /// number of index packets written so far
};

} /// end namespace e57

#endif // E57FORMATIMPL_H_INCLUDED