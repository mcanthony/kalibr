#ifndef ASLAM_BACKEND_MATRIX_EXPRESSION_HPP
#define ASLAM_BACKEND_MATRIX_EXPRESSION_HPP

#include <Eigen/Core>
#include <boost/shared_ptr.hpp>
#include <aslam/backend/JacobianContainer.hpp>
#include "HomogeneousExpression.hpp"
#include "EuclideanExpression.hpp"
#include "TransformationExpression.hpp"
#include <set>

namespace aslam {
  namespace backend {
    
    class MatrixExpressionNode;
    class TransformationExpression;
    class EuclideanExpression;
    class HomogeneousExpression;

    class MatrixExpression
    {
    public:
      /// \brief initialize from an existing node.
      MatrixExpression(boost::shared_ptr<MatrixExpressionNode> root);

      /// \brief Initialize from an existing node. The node will not be deleted.
      MatrixExpression(MatrixExpressionNode * root);
      
      virtual ~MatrixExpression();

      /// \brief Evaluate the full transformation matrix.
      Eigen::Matrix3d toFullMatrix();

      /// \brief return the expression that inverts the transformation.
      MatrixExpression inverse();
      
      /// \brief Evaluate the Jacobians in the form (1 - (S \delta v)^\times) \bar C
      void evaluateJacobians(JacobianContainer & outJacobians) const;

      MatrixExpression operator*(const MatrixExpression & p);
      EuclideanExpression operator*(const EuclideanExpression & p);
      HomogeneousExpression operator*(const HomogeneousExpression & p);

      TransformationExpression toTransformationExpression();

      void getDesignVariables(DesignVariable::set_t & designVariables) const;

      boost::shared_ptr<MatrixExpressionNode> root() { return _root; }
    private:

      MatrixExpression();
      boost::shared_ptr<MatrixExpressionNode> _root;
    };

  } // namespace backend
} // namespace aslam


#endif /* ASLAM_BACKEND_MATRIX_EXPRESSION_HPP */
