///add class

#ifndef vtkOvalSoutce_h
#define vtkOvalSoutce_h
#include "vtkFiltersSourcesModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class VTKFILTERSSOURCES_EXPORT vtkOvalSoutce : public vtkPolyDataAlgorithm
{
public:
    //@{
    /**
     * Standard methods for instantiation, obtaining type and printing instance values.
     */
    static vtkOvalSoutce* New();
    vtkTypeMacro(vtkOvalSoutce, vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;
    //@}

    //@{
    /**
     * Set/Get the number of sides of the polygon. By default, the number of sides
     * is set to six.
     */
    vtkSetClampMacro(NumberOfSides, int, 3, VTK_INT_MAX);
    vtkGetMacro(NumberOfSides, int);
    //@}

    //@{
    /**
     * Set/Get the center of the polygon. By default, the center is set at the
     * origin (0,0,0).
     */
    vtkSetVector3Macro(Center, double);
    vtkGetVectorMacro(Center, double, 3);
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

    //@{
    /**
     * Set/Get the radius of the polygon. By default, the radius is set to 0.5.
     */
    vtkSetMacro(AxisX, double);
    vtkGetMacro(AxisX, double);
    vtkSetMacro(AxisY, double);
    vtkGetMacro(AxisY, double);
    //@}

    //@{
    /**
     * Control whether a polygon is produced. By default, GeneratePolygon is enabled.
     */
    vtkSetMacro(GeneratePolygon, vtkTypeBool);
    vtkGetMacro(GeneratePolygon, vtkTypeBool);
    vtkBooleanMacro(GeneratePolygon, vtkTypeBool);
    //@}

    //@{
    /**
     * Control whether a polyline is produced. By default, GeneratePolyline is enabled.
     */
    vtkSetMacro(GeneratePolyline, vtkTypeBool);
    vtkGetMacro(GeneratePolyline, vtkTypeBool);
    vtkBooleanMacro(GeneratePolyline, vtkTypeBool);
    //@}

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
    vtkOvalSoutce();
    ~vtkOvalSoutce() override {}

    int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

    int    NumberOfSides;
    double Center[3];
    double Normal[3];
    double AxisX;
    double AxisY;
    vtkTypeBool    GeneratePolygon;
    vtkTypeBool    GeneratePolyline;
    int    OutputPointsPrecision;

private:
    vtkOvalSoutce(const vtkOvalSoutce&) = delete;
    void operator=(const vtkOvalSoutce&) = delete;
};

#endif
