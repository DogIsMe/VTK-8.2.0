#ifndef vtkArrow2D_h
#define vtkArrow2D_h

#include "vtkFiltersSourcesModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class VTKFILTERSSOURCES_EXPORT vtkArrow2D : public vtkPolyDataAlgorithm
{
public:
    //@{
    /**
     * Standard methods for instantiation, obtaining type and printing instance values.
     */
    static vtkArrow2D* New();
    vtkTypeMacro(vtkArrow2D, vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;
    //@}
    /**
     * Set/Get the center of the polygon. By default, the center is set at the
     * origin (0,0,0).
     */
    vtkSetVector3Macro(End, double);
    vtkGetVectorMacro(End, double, 3);
    vtkSetVector3Macro(Start, double);
    vtkGetVectorMacro(Start, double, 3);
    //@}

    //@{
    /**
     * Set/Get the normal to the polygon. The ordering of the polygon will be
     * counter-clockwise around the normal (i.e., using the right-hand rule).
     * By default, the normal is set to (0,0,1).
     */
    vtkSetVector3Macro(Normal, double);
    vtkGetVectorMacro(Normal, double, 3);
    //@}

    vtkSetMacro(Theta, double);
    vtkGetMacro(Theta, double);


    vtkSetMacro(TipLength, double);
    vtkGetMacro(TipLength, double);

    //@{
    /**
     * Set/get the desired precision for the output points.
     * vtkAlgorithm::SINGLE_PRECISION - Output single-precision floating point.
     * vtkAlgorithm::DOUBLE_PRECISION - Output double-precision floating point.
     */
    vtkSetMacro(OutputPointsPrecision, int);
    vtkGetMacro(OutputPointsPrecision, int);
    //@}

protected:
    vtkArrow2D();
    ~vtkArrow2D() override {}

    int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
    double End[3];
    double Start[3];
    double Normal[3];
    int    OutputPointsPrecision;
    double Theta;
    double TipLength;
private:
    vtkArrow2D(const vtkArrow2D&) = delete;
    void operator=(const vtkArrow2D&) = delete;
};

#endif