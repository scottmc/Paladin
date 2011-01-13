#include "PMethod.h"
#include <Errors.h>

PMethod::PMethod(const char *name, MethodFunction func, PMethodInterface *interface,
				const int32 &flags)
	:	fName(name),
		fFlags(flags)
{
	fFunction = func;
	if (interface)
		fInterface = *interface;
}


PMethod::~PMethod(void)
{
}


PMethod &
PMethod::operator=(const PMethod &from)
{
	fName = from.fName;
	
	return *this;
}


void
PMethod::SetName(const char *name)
{
	fName = name;
}


void
PMethod::SetName(const BString &name)
{
	SetName(name.String());
}


BString
PMethod::GetName(void) const
{
	return fName;
}


void
PMethod::SetInterface(PMethodInterface &interface)
{
	
}


void
PMethod::GetInterface(PMethodInterface &interface)
{
}

	
void
PMethod::SetDescription(const char *string)
{
	fDescription = string;
}


void
PMethod::SetDescription(const BString &string)
{
	SetDescription(string.String());
}


BString
PMethod::GetDescription(void) const
{
	return fDescription;
}

	
void
PMethod::SetFunction(MethodFunction func)
{
	fFunction = func;
}


MethodFunction
PMethod::GetFunction(void) const
{
	return fFunction;
}


status_t
PMethod::Run(PObject *object, PArgList &in, PArgList &out)
{
	return fFunction(object, &in, &out);
}


PMethodInterface::PMethodInterface(void)
	:	fIn(20, true),
		fOut(20, true)
{
}


PMethodInterface::PMethodInterface(PMethodInterface &from)
	:	fIn(20, true),
		fOut(20, true)
{
}


PMethodInterface::~PMethodInterface(void)
{
}


PMethodInterface &
PMethodInterface::operator=(const PMethodInterface &from)
{
	SetTo(from);
	return *this;
}


void
PMethodInterface::SetTo(const PMethodInterface &from)
{
	MakeEmpty();
	for (int32 i = 0; i < from.CountArgs(); i++)
	{
		PMethodInterfaceData *data = from.fIn.ItemAt(i);
		if (data)
			fIn.AddItem(new PMethodInterfaceData(*data));
	}
	
	for (int32 j = 0; j < from.CountArgs(); j++)
	{
		PMethodInterfaceData *data = from.fOut.ItemAt(j);
		if (data)
			fOut.AddItem(new PMethodInterfaceData(*data));
	}
}


void
PMethodInterface::MakeEmpty(void)
{
	fIn.MakeEmpty();
	fOut.MakeEmpty();
}


status_t
PMethodInterface::SetArg(const int32 &index, const char *name,
						const PArgType &type, const char *description)
{
	if (!name)
		return B_ERROR;
	
	PMethodInterfaceData *data = fIn.ItemAt(index);
	if (!data)
		return B_ERROR;
	
	data->name = name;
	data->type = type;
	data->description = description;
	
	return B_OK;
}


status_t
PMethodInterface::AddArg(const char *name, const PArgType &type,
						const char *description)
{
	if (!name)
		return B_ERROR;
	
	if (FindArg(name) >= 0)
		return B_NAME_IN_USE;
	
	return fIn.AddItem(new PMethodInterfaceData(name, type, description)) ? B_OK : B_ERROR;
}


status_t
PMethodInterface::RemoveArg(const int32 &index)
{
	return fIn.RemoveItem(fIn.ItemAt(index)) ? B_OK : B_ERROR;
}



BString
PMethodInterface::ArgNameAt(const int32 &index)
{
	PMethodInterfaceData *data = fIn.ItemAt(index);
	return data ? data->name : BString();
}


PArgType
PMethodInterface::ArgTypeAt(const int32 &index)
{
	PMethodInterfaceData *data = fIn.ItemAt(index);
	return data ? data->type : PARG_END;
}


BString
PMethodInterface::ArgDescAt(const int32 &index)
{
	PMethodInterfaceData *data = fIn.ItemAt(index);
	return data ? data->description : BString();
}


int32
PMethodInterface::CountArgs(void) const
{
	return fIn.CountItems();
}


int32
PMethodInterface::FindArg(const char *name) const
{
	for (int32 i = 0; i < fIn.CountItems(); i++)
	{
		PMethodInterfaceData *data = fIn.ItemAt(i);
		if (data->name.ICompare(name) == 0)
			return i;
	}
	return -1;
}


status_t
PMethodInterface::SetReturnValue(const int32 & index, const char *name,
						const PArgType &type, const char *description)
{
	if (!name)
		return B_ERROR;
	
	PMethodInterfaceData *data = fOut.ItemAt(index);
	if (!data)
		return B_ERROR;
	
	data->name = name;
	data->type = type;
	data->description = description;
	
	return B_OK;
}


status_t
PMethodInterface::AddReturnValue(const char *name, const PArgType &type,
						const char *description)
{
	if (!name)
		return B_ERROR;
	
	if (FindReturnValue(name) >= 0)
		return B_NAME_IN_USE;
	
	return fOut.AddItem(new PMethodInterfaceData(name, type, description)) ? B_OK : B_ERROR;
}


status_t
PMethodInterface::RemoveReturnValue(const int32 &index)
{
	return fOut.RemoveItem(fOut.ItemAt(index)) ? B_OK : B_ERROR;
}



BString
PMethodInterface::ReturnNameAt(const int32 &index)
{
	PMethodInterfaceData *data = fOut.ItemAt(index);
	return data ? data->name : BString();
}


PArgType
PMethodInterface::ReturnTypeAt(const int32 &index)
{
	PMethodInterfaceData *data = fOut.ItemAt(index);
	return data ? data->type : PARG_END;
}


BString
PMethodInterface::ReturnDescAt(const int32 &index)
{
	PMethodInterfaceData *data = fOut.ItemAt(index);
	return data ? data->description : BString();
}


int32
PMethodInterface::CountReturnValues(void) const
{
	return fOut.CountItems();
}


int32
PMethodInterface::FindReturnValue(const char *name) const
{
	for (int32 i = 0; i < fOut.CountItems(); i++)
	{
		PMethodInterfaceData *data = fOut.ItemAt(i);
		if (data->name.ICompare(name) == 0)
			return i;
	}
	return -1;
}

