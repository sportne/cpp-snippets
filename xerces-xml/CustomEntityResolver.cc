#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/sax/InputSource.hpp>

using namespace xercesc;

class NoEntityResolver : public XERCES_CPP_NAMESPACE::EntityResolver
{
public:
    InputSource* resolveEntity(const XMLCh* const publicId,
                               const XMLCh* const systemId) override
    {
        return nullptr;
    }
};

int main(int argc, char* argv[])
{
    // Initialize the Xerces library
    XMLPlatformUtils::Initialize();

    // Create a DOM parser
    std::unique_ptr<SAX2XMLReader> parser(XMLReaderFactory::createXMLReader());

    // Create a NoEntityResolver object and set it on the parser
    NoEntityResolver entityResolver;
    parser->setEntityResolver(&entityResolver);

    // Parse an XML file
    parser->parse(argv[1]);

    // Terminate the Xerces library
    XMLPlatformUtils::Terminate();
    return 0;
}
