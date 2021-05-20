#include "vtkArrow2D.h"

#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkObjectFactory.h"
#include "vtkMath.h"

vtkStandardNewMacro(vtkArrow2D);

vtkArrow2D::vtkArrow2D()
{
    this->End[0] = 0.0; this->End[1] = 0.0; this->End[2] = 0.0;
    this->Start[0] = 0.0; this->Start[1] = -10.0; this->Start[2] = 0.0;
    this->Normal[0] = 0.0; this->Normal[1] = 0.0; this->Normal[2] = 1.0;
    this->Theta = vtkMath::Pi() / 8;
    this->TipLength = 0.5;
    this->OutputPointsPrecision = SINGLE_PRECISION;

    this->SetNumberOfInputPorts(0);
}

int vtkArrow2D::RequestData(
    vtkInformation* vtkNotUsed(request),
    vtkInformationVector** vtkNotUsed(inputVector),
    vtkInformationVector* outputVector)
{
    // Get the info object
    vtkInformation* outInfo = outputVector->GetInformationObject(0);

    // Get the output
    vtkPolyData* output = vtkPolyData::SafeDownCast(
        outInfo->Get(vtkDataObject::DATA_OBJECT()));

    double x[3], r[3];
    vtkPoints* newPoints;
    // Prepare to produce the output; create the connectivity array(s)
    newPoints = vtkPoints::New();

    // Set the desired precision for the points in the output.
    if (this->OutputPointsPrecision == vtkAlgorithm::DOUBLE_PRECISION)
    {
        newPoints->SetDataType(VTK_DOUBLE);
    }
    else
    {
        newPoints->SetDataType(VTK_FLOAT);
    }

    vtkCellArray* newLine;
    newLine = vtkCellArray::New();
    newLine->Allocate(newLine->EstimateSize(3, 2));
    vtkIdType pts[2];
    pts[0] = 0; pts[1] = 1; 
    newLine->InsertNextCell(2,pts);
    pts[0] = 0; pts[1] = 2;
    newLine->InsertNextCell(2, pts);
    pts[0] = 0; pts[1] = 3;
    newLine->InsertNextCell(2, pts);
    output->SetLines(newLine);
    newLine->Delete();
    
    // Produce a unit vector in the plane of the polygon (i.e., perpendicular
    // to the normal)
 
    double n[3], axis[3], px[3], py[3];

    // Make sure the polygon normal is a unit vector
    n[0] = this->Normal[0];
    n[1] = this->Normal[1];
    n[2] = this->Normal[2];
    if (vtkMath::Normalize(n) == 0.0)
    {
        n[0] = 0.0;
        n[1] = 0.0;
        n[2] = 1.0;
    }

    // Cross with unit axis vectors and eventually find vector in the polygon plane
    int foundPlaneVector = 0;
    axis[0] = 1.0;
    axis[1] = 0.0;
    axis[2] = 0.0;
    vtkMath::Cross(n, axis, px);
    if (vtkMath::Normalize(px) > 1.0E-3)
    {
        foundPlaneVector = 1;
    }
    if (!foundPlaneVector)
    {
        axis[0] = 0.0;
        axis[1] = 1.0;
        axis[2] = 0.0;
        vtkMath::Cross(n, axis, px);
        if (vtkMath::Normalize(px) > 1.0E-3)
        {
            foundPlaneVector = 1;
        }
    }
    if (!foundPlaneVector)
    {
        axis[0] = 0.0;
        axis[1] = 0.0;
        axis[2] = 1.0;
        vtkMath::Cross(n, axis, px);
        vtkMath::Normalize(px);
    }
    vtkMath::Cross(px, n, py); //created two orthogonal axes in the polygon plane, px & py

    // Now run around normal vector to produce polygon points.
    double theta = vtkMath::Pi() * (1-this->Theta);
   
        for (int i = 0; i < 3; i++)
        {
            r[i] = px[i] * cos(theta) + py[i] * sin(theta);
            x[i] = this->End[i] + this->TipLength * r[i];
        }
        newPoints->InsertNextPoint(this->End);
        newPoints->InsertNextPoint(x);
        theta = vtkMath::Pi() * (1 + this->Theta);
        for (int i = 0; i < 3; i++)
        {
            r[i] = px[i] * cos(theta) + py[i] * sin(theta);
            x[i] = this->End[i] + this->TipLength * r[i];
        }
        newPoints->InsertNextPoint(x);
        newPoints->InsertNextPoint(this->Start);
    output->SetPoints(newPoints);
    newPoints->Delete();

    return 1;
}

void vtkArrow2D::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);

    os << indent << "Start: (" << this->Start[0] << ", "
        << this->Start[1] << ", "
        << this->Start[2] << ")\n";
    os << indent << "End: (" << this->End[0] << ", "
        << this->End[1] << ", "
        << this->End[2] << ")\n";

    os << indent << "Normal: (" << this->Normal[0] << ", "
        << this->Normal[1] << ", "
        << this->Normal[2] << ")\n";

    os << indent << "Theta: (" << this->Theta << ")\n";

    os << indent << "TipLength: (" << this->TipLength << ")\n";

    os << indent << "Output Points Precision: " << this->OutputPointsPrecision << "\n";
}
