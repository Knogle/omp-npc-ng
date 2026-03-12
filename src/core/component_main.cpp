#include <sdk.hpp>

static const UID OMPNPCNG_UID = UID(0x14a1f8bdb1934d01);

class OmpNpcNgComponent final : public IComponent
{
public:
	PROVIDE_UID(OMPNPCNG_UID);

	StringView componentName() const override
	{
		return "OMPNPCNG";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(OMP_VERSION_MAJOR, OMP_VERSION_MINOR, OMP_VERSION_PATCH, BUILD_NUMBER);
	}

	void onLoad(ICore* c) override
	{
		core_ = c;
	}

	void free() override
	{
		delete this;
	}

	void reset() override
	{
	}

private:
	ICore* core_ = nullptr;
};

COMPONENT_ENTRY_POINT()
{
	return new OmpNpcNgComponent();
}
