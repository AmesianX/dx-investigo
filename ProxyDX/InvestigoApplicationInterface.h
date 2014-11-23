//Copyright (C) 2012 Ashley Davis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
//documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#pragma once

#include <windows.h>
#include <string>

#ifdef INVESTIGO_ENABLED

///
// Namespace for Investigo application interface.
///
namespace Investigo
{
    ///
    // Specifies the type of an Investigo variable.
    ///
    enum VariableType
    {
        VariableType_Int,
        VariableType_Double,
        VariableType_Memory,
        VariableType_Milliseconds,
    };
 
    ///
    // Interface to a variable.
    ///
    class IVariable
    {
    public:

        ///
        // Set the value of the variable as an int.
        ///
        virtual void SetValue(int value) = 0;

        ///
        // Increment the value of the variable (int's only).
        ///
        virtual void Increment() = 0;

        ///
        // Set the value of the variable as a double.
        ///
        virtual void SetValue(double value) = 0;

        ///
        // Reset the value of the variable.
        ///
        virtual void Reset() = 0;
    };

    ///
    // Interface to Investigo resources (eg proxied DirectX resources).
    ///
    [uuid("76D3B439-8798-4017-A102-2A4CA10BF135")]
    class IResource : public IUnknown
    {
    public:
        //
        // IUnknown methods.
        //
        STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
        STDMETHOD_(ULONG,AddRef)(THIS) PURE;
        STDMETHOD_(ULONG,Release)(THIS) PURE;

        ///
        // Get the resource's unique ID.
        ///
        virtual int GetId() const = 0;

        ///
        // Get the human readable name of the resource.
        ///
        virtual const std::string& GetName() const = 0;

    };

    ///
    /// Application interface to Investigo.
    /// Used by the application to interact directly with Investigo.
    ///
    /// You should prefer not to use this interface, convenient and simpler inline functions are defined below.
    ///
    class Interface
    {
    public:

        ///
        /// Get the current frame number, starting at 1.
        ///
        virtual int GetFrameNumber() const = 0;

        ///
        /// Get current time in seconds as measured by Investigo.
        ///
        virtual double GetTime() const = 0;

		///
		/// Set the directory that Investigo outputs log files to.
		/// This must be set before performance logging is started.
		///
		virtual void SetOutputDirectory(const char* outputDirectory) = 0;

	    ///
	    /// Enable/disable draw calls.
	    ///
	    virtual void EnableDrawCalls(bool enable) = 0;

	    ///
	    /// Begin a section of code that loads a resource.
        /// Resources that are loaded (eg textures and shaders) will inherit the specified resource name.
        /// Calls can be nested.
	    ///
	    virtual void BeginResource(const char* resourceName) = 0;

        /// 
        /// End a section of code that loads a resource.
        ///
	    virtual void EndResource() = 0;

        /// 
        /// Begin a section of code that renders a technique.
        /// Textures/shaders that are set can be associated with the technique (this is used by the D3DX proxy). 
        ///
	    virtual void BeginTechnique(const char* techinqueName) = 0;

        ///
        /// End a section of code that renders a technique.        
        ///
	    virtual void EndTechnique() = 0;

        ///
        /// Retrieve a variable from a named page.
        /// Variable and page are created if they doen't exist.
        ///
        virtual IVariable* GetVariable(const char* pageName, const char* variableName, VariableType variableType) = 0;

        ///
        /// Returns true if performance logging is currently enabled, or queued to start next frame.
        ///
        virtual bool IsPerformanceLoggingEnabled() = 0;

        ///
        /// Starts performance logging.
        ///
        virtual void StartPerformanceLogging() = 0;

        ///
        /// Stops performance logging.
        ///
        virtual void StopPerformanceLogging() = 0;

        ///
        /// Get the current frame number (starts at 1).
        ///
        virtual int GetCurrentFrameNumber() const = 0;

        ///
        /// Starts performance logging at the specified frame number.
        /// Has no effect if the specified frame has already passed.
        ///
        virtual void StartPerformanceLoggingAt(int frameNumber) = 0;

        ///
        /// Stops performance logging after X frames.
        ///
        virtual void StopPerformanceLoggingAfter(int numFrames) = 0;

        ///
        /// Causes the application to be forcefully exited when performance logging has finished.
        ///
        virtual void ExitWhenPerformanceLoggingFinished() = 0;
    };


    ///
    /// Define a function that loads the application interface from the Investigo DLL.
    ///
    typedef Interface* (*__stdcall pfnGetInterface)();


    ///
    /// Load the Investigo DLL and retrieve the application interface.
    /// The interface is cached, subsequent calls simply return it.
    ///
    inline Interface* EnsureLoaded()
    {
        static bool loadAttempted = false;
        static Interface* applicationInterface = NULL;
        if (!loadAttempted)
        {
            loadAttempted = true; /// Don't try to load more than once, if the load failed.

            static HMODULE hLibrary = LoadLibraryA("d3d9.dll");
            if (hLibrary)
            {
                pfnGetInterface getApplicationInterface = (pfnGetInterface) GetProcAddress(hLibrary, "GetApplicationInterface");
                if (getApplicationInterface)
                {
                    applicationInterface = getApplicationInterface();
                }
            }
        }
        
	    return applicationInterface;
    }

	///
	/// Enable or disable draw calls.
	///
	inline void EnableDrawCalls(bool enable)
	{
		if (Interface* applicationInterface = EnsureLoaded())
		{
			applicationInterface->EnableDrawCalls(enable);
		}
	}

	///
	/// Enable draw calls.
	///
	inline void EnableDrawCalls() { EnableDrawCalls(true); }

	///
	/// Disable draw calls.
	///
	inline void DisableDrawCalls() { EnableDrawCalls(false); }

    ///
    /// Begin a section of code that loads resources.
    ///
    inline void ResourceBegin(const char* resourceName)
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->BeginResource(resourceName);
        }
    }

    ///
    /// End a section of code that loads resources.
    ///
    inline void ResourceEnd()
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->EndResource();
        }
    }

    ///
    /// Get the name of a DirectX resource.
    ///
    inline std::string GetResourceName(IUnknown* iface)
    {
        IResource* investigoResource = NULL; 
        if (SUCCEEDED(iface->QueryInterface(__uuidof(IResource), (void**) &investigoResource)))
        {
            std::string name = investigoResource->GetName();
            investigoResource->Release();
            return name.size() > 0 ? name : "unamed";
        }

        return "invalid";
    }

    ///
    /// Begin rendering of an effect technique.
    ///
    inline void TechniqueBegin(const char* techniqueName)
    {
	    if (Interface* applicationInterface = EnsureLoaded())
	    {
		    applicationInterface->BeginTechnique(techniqueName);
	    }
    }

    ///
    /// End rendering of an effect technique.
    ///
    inline void TechniqueEnd()
    {
	    if (Interface* applicationInterface = EnsureLoaded())
	    {
		    applicationInterface->EndTechnique();
	    }
    }

	///
	/// Set the directory that Investigo outputs log files to.
	/// This must be set before performance logging is started.
	///
	inline void SetOutputDirectory(const char* outputDirectory)
	{
		if (Interface* applicationInterface = EnsureLoaded())
		{
			applicationInterface->SetOutputDirectory(outputDirectory);
		}
	}

    ///
    /// Returns true if performance logging is currently enabled, or queued to start next frame.
    ///
    inline bool IsPerformanceLoggingEnabled()
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            return applicationInterface->IsPerformanceLoggingEnabled();
        }

        return false;
    }

    ///
    /// Starts performance logging.
    ///
    inline void StartPerformanceLogging()
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->StartPerformanceLogging();
        }
    }

    ///
    /// Stops performance logging.
    ///
    inline void StopPerformanceLogging()
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->StopPerformanceLogging();
        }
    }

    ///
    /// Get the current frame number (starts at 1).
    /// Returns 0 when Investigo is not loaded.
    ///
    inline int GetCurrentFrameNumber()
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            return applicationInterface->GetCurrentFrameNumber();
        }

        return 0;
    }

    ///
    /// Starts performance logging at the specified frame number.
    /// Has no effect if the specified frame has already passed.
    ///
    inline void StartPerformanceLoggingAt(int frameNumber)
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->StartPerformanceLoggingAt(frameNumber);
        }
    }

    ///
    /// Stops performance logging after X frames.
    ///
    inline void StopPerformanceLoggingAfter(int numFrames)
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->StopPerformanceLoggingAfter(numFrames);
        }
    }

    ///
    /// Causes the application to be forcefully exited when performance logging has finished.
    ///
    inline void ExitWhenPerformanceLoggingFinished()
    {
        if (Interface* applicationInterface = EnsureLoaded())
        {
            applicationInterface->ExitWhenPerformanceLoggingFinished();
        }
    }

    ///
    /// A handle to an Investigo variable.
    ///
    class VariableHandle
    {
    public:

        VariableHandle(const char* pageName, const char* variableName, VariableType variableType)
        {
            if (Interface* applicationInterface = EnsureLoaded())
            {
                variable = applicationInterface->GetVariable(pageName, variableName, variableType);
            }
            else
            {
                variable = NULL;
            }
        }

        ///
        /// Reset the variable.
        ///
        void Reset()
        {
            if (variable)
            {
                variable->Reset();
            }
        }

        ///
        /// Increment the variable (int's only).
        ///
        void Increment()
        {
            if (variable)
            {
                variable->Increment();
            }
        }

        /// 
        /// Set the int value of the variable.
        ///
        void SetValue(int value)
        {
            if (variable)
            {
                variable->SetValue(value);
            }
        }

        /// 
        /// Set the double value of the variable.
        ///
        void SetValue(double value)
        {
            if (variable)
            {
                variable->SetValue(value);
            }
        }

        ///
        /// The cached pointer to the variable interface.
        ///
        IVariable* variable;
    };

    ///
    /// Times a block of code, recording the elapsed time in a variable.
    ///
    class TimingBlock
    {
    public:

        ///
        /// Constructor captures start time.
        ///
        TimingBlock(IVariable* _variable) :
            variable(_variable)
        {
            if (Interface* applicationInterface = EnsureLoaded())
            {
                startTime = applicationInterface->GetTime();
            }
            else
            {
                startTime = 0.0;
            }
        }

        ///
        /// Destructor captures end time, then records the elapsed time in the variable.
        ///
        ~TimingBlock()
        {
            if (Interface* applicationInterface = EnsureLoaded())
            {
                double endTime = applicationInterface->GetTime();
                double elapsedTime = endTime - startTime;
                variable->SetValue(elapsedTime);
            }
        }

    private:

        /// 
        /// The time that the code started.
        ///
        double startTime;

        /// 
        /// Variable that records the timing.
        ///
        IVariable* variable;

        ///
        /// Application interface for retrieving current time.
        ///
        Interface* applicationInterface;
    };

}

///
/// Enable Investigo Macros.
///

///
/// Set the value of an investigo int variable.
///
#define INVESTIGO_INT_SET_VALUE(page, name, value) \
    { \
        static Investigo::Variable::Handle variable(#page, #name, VariableType_Int); \
        variable.SetValue(value); \
    }

///
/// Increment the value of an investigo int variable.
///
#define INVESTIGO_INT_INCREMENT(page, name) \
    { \
        static Investigo::Variable::Int variable(#page, #name, VariableType_Int); \
        variable.Increment(); \
    }

///
/// Reset the value of an investigo int variable.
///
#define INVESTIGO_INT_RESET(page, name) \
    { \
        static Investigo::Variable::Int variable(#page, #name, VariableType_Int); \
        variable.Reset(); \
    }

///
/// Set the value of an investigo double variable.
///
#define INVESTIGO_DOUBLE_SET_VALUE(page, name, value) \
    { \
        static Investigo::Variable::Double variable(#page, #name, VariableType_Double); \
        variable.SetValue(value); \
    }

///
/// Reset the value of an investigo double variable.
///
#define INVESTIGO_DOUBLE_RESET(page, name) \
    { \
        static Investigo::Variable::Double variable(#page, #name, VariableType_Double); \
        variable.Reset(); \
    }

///
/// Measure the execution duration of a block of code.
///
#define INVESTIGO_TIMER(page, name) \
    static Investigo::Variable::Handle __investigoTimingID##name(#page, #name, VariableType_Double); \
    Investigo::Timing::Block __investigoTiming##name(__investigoTimingID##name.variable); 

///
/// Retrieve the name that has been assigned to a DirectX resource.
///
#define INVESTIGO_RESOURCE_NAME(iface)  Investigo::Resource::GetResourceName(iface)

///
/// Start a block of code where loaded DirectX resources will be annotated with the specified name.
/// 
#define INVESTIGO_RESOURCE_BEGIN(name)  Investigo::Resource::Begin(name)

///
/// End a block of code where loaded DirectX resources will be annotated with the specified name.
/// 
#define INVESTIGO_RESOURCE_END          Investigo::Resource::End()


#else /// INVESTIGO_ENABLED

///
/// Disable Investigo Macros.
///

#define INVESTIGO_INT_SET_VALUE(page, name, value)
#define INVESTIGO_INT_INCREMENT(page, name)
#define INVESTIGO_INT_RESET(page, name)
#define INVESTIGO_DOUBLE_SET_VALUE(page, name, value)
#define INVESTIGO_DOUBLE_RESET(page, name)
#define INVESTIGO_TIMER(page, name)
#define INVESTIGO_RESOURCE_NAME(iface) ("INVESTIGO_ENABLED-not-defined")
#define INVESTIGO_RESOURCE_BEGIN(name)
#define INVESTIGO_RESOURCE_END

#endif /// INVESTIGO_ENABLED
