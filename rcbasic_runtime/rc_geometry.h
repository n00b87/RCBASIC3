#include "rc_matrix.h"

#ifndef RC_GEOMETRY_H_INCLUDED
#define RC_GEOMETRY_H_INCLUDED


// ------------------ 3D Transform Routines --------------------------------


double CalculateFaceZ(double cam_dist, double graph_offset_x, double graph_offset_y, double view_w, double view_h, double view_depth, uint32_t mA, int f_vertex_count, double* columns, double* face_min_z, double* face_max_z, double* z_avg)
{
    bool dbg = false;

	if(f_vertex_count > 4)
		return -1;


	double vx, vy, vz[4];

	int oi_count = 0;


	double n_face_min_z = MatrixValue(mA, 2, (uint32_t)columns[0]);
	double n_face_max_z = n_face_min_z;


	bool in_zx_range = false;
	bool in_zy_range = false;

	double face_min_x = 0;
	double face_max_x = 0;

	double face_min_y = 0;
	double face_max_y = 0;

	bool zx_min_bound = false;
	bool zx_max_bound = false;

	bool zy_min_bound = false;
	bool zy_max_bound = false;

	double distance = 0;

	double z_dist = 0; //C3D_CAMERA_LENS - z
	double off_x = graph_offset_x;
	double off_y = graph_offset_y;

    double min_x = (0 - off_x) / cam_dist;
    double min_y = (view_h - off_y) / cam_dist * -1;

    double max_x = (view_w - off_x) / cam_dist;
    double max_y = (0 - off_y) / cam_dist * -1;

    double zx_min, zx_max, zy_min, zy_max;

	for(int i = 0; i < f_vertex_count; i++)
    {
        vz[i] = MatrixValue(mA, 2, (uint32_t)columns[i]);
		vx = MatrixValue(mA, 0, (uint32_t)columns[i]);
		vy = MatrixValue(mA, 1, (uint32_t)columns[i]);


		distance = -1*vz[i];

		if(distance >= 0 && distance < view_depth)
        {
            double d = cam_dist - (distance*-1);
            zx_min = min_x * d;
            zx_max = max_x * d;
            zy_min = min_y * d;
            zy_max = max_y * d;

			in_zx_range = in_zx_range || (vx >= zx_min && vx < zx_max);
			in_zy_range = in_zy_range || (vy >= zy_min && vy < zy_max);

			zx_min_bound = zx_min_bound || (vx < zx_min);
			zx_max_bound = zx_max_bound || (vx >= zx_max);

			zy_min_bound = zy_min_bound || (vy < zy_min);
			zy_max_bound = zy_max_bound || (vy >= zy_max);
        }
		else if(vz[i] >= 0 && vz[i] < view_depth)
        {
            double d = cam_dist - (vz[i]*-1);
            zx_min = min_x * d;
            zx_max = max_x * d;
            zy_min = min_y * d;
            zy_max = max_y * d;

            in_zx_range = in_zx_range || (vx >= zx_min && vx < zx_max);
			in_zy_range = in_zy_range || (vy >= zy_min && vy < zy_max);

			zx_min_bound = zx_min_bound || (vx < zx_min);
			zx_max_bound = zx_max_bound || (vx >= zx_max);

			zy_min_bound = zy_min_bound || (vy < zy_min);
			zy_max_bound = zy_max_bound || (vy >= zy_max);
        }

		n_face_min_z = min(n_face_min_z, vz[i]);
		n_face_max_z = max(n_face_max_z, vz[i]);

    }

	in_zx_range = in_zx_range || (zx_min_bound && zx_max_bound);
	in_zy_range = in_zy_range || (zy_min_bound && zy_max_bound);

	if( (!in_zx_range) || (!in_zy_range) )
		return -1;

	//'if key(k_i) and actor = 1 then : print "face = ";face_num : end if

	z_avg[0] = (n_face_min_z+n_face_max_z) / 2; //'This is some bullshit math to order the faces with out checking if they are obscured

	face_min_z[0] = n_face_min_z;
	face_max_z[0] = n_face_max_z;

	//C3D_Actor_Face_ZOrder[actor, face_num] = face_min_z


	if(face_min_z[0] >= cam_dist)
		return -1;
	else
		return (cam_dist - face_min_z[0]);


}



int LinePlaneIntersection(double* line_point, double* line_direction, double* plane_point_1, double* plane_point_2, double* plane_point_3, double* intersection)
{
	//'    """
	//'    Calculates the intersection point of a line and a plane in 3D space.
	//'
	//'    Parameters:
	//'    line_point (tuple or list): a point on the line (x, y, z)
	//'    line_direction (tuple or list): the direction vector of the line (x, y, z)
	//'    plane_point_1 (tuple or list): one point on the plane (x, y, z)
	//'    plane_point_2 (tuple or list): another point on the plane (x, y, z)
	//'    plane_point_3 (tuple or list): a third point on the plane (x, y, z)
	//'
	//'    Returns:
	//'    intersection (tuple): the intersection point (x, y, z), or None if the line is parallel to the plane
	//'    """
	//'    # calculate the normal vector of the plane using the cross product of two vectors on the plane

	double plane_vector_1[3], plane_vector_2[3], plane_normal[3];

	plane_vector_1[0] = plane_point_2[0] - plane_point_1[0];
	plane_vector_1[1] = plane_point_2[1] - plane_point_1[1];
	plane_vector_1[2] = plane_point_2[2] - plane_point_1[2];

	plane_vector_2[0] = plane_point_3[0] - plane_point_1[0];
	plane_vector_2[1] = plane_point_3[1] - plane_point_1[1];
	plane_vector_2[2] = plane_point_3[2] - plane_point_1[2];

	plane_normal[0] = plane_vector_1[1] * plane_vector_2[2] - plane_vector_1[2] * plane_vector_2[1];
	plane_normal[1] = plane_vector_1[2] * plane_vector_2[0] - plane_vector_1[0] * plane_vector_2[2];
	plane_normal[2] = plane_vector_1[0] * plane_vector_2[1] - plane_vector_1[1] * plane_vector_2[0];

	//'# calculate the scalar value of t using the line equation
	double t = ((plane_point_1[0] - line_point[0]) * plane_normal[0] + (plane_point_1[1] - line_point[1]) * plane_normal[1] + (plane_point_1[2] - line_point[2]) * plane_normal[2]);
	//'print "t1 = ";t
	t = t / (line_direction[0] * plane_normal[0] + line_direction[1] * plane_normal[1] + line_direction[2] * plane_normal[2]);
	//'print "t2 = ";(line_direction[0] * plane_normal[0] + line_direction[1] * plane_normal[1] + line_direction[2] * plane_normal[2])

	//'# calculate the intersection point using the line equation
	intersection[0] = line_point[0] + t * line_direction[0];
	intersection[1] = line_point[1] + t * line_direction[1];
	intersection[2] = line_point[2] + t * line_direction[2];

	//'# check if the intersection point is on the plane
	double plane_distance = abs((intersection[0] - plane_point_1[0]) * plane_normal[0] + (intersection[1] - plane_point_1[1]) * plane_normal[1] + (intersection[2] - plane_point_1[2]) * plane_normal[2]);
	if(plane_distance < 10^-6)
		return true;
	else
		return false;

}

double Distance3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt( pow((x2 - x1),2) + pow((y2 - y1),2) + pow((z2 - z1),2) );
}

double Interpolate(double min_a, double max_a, double mid_a, double min_b, double max_b)
{
	return ( (mid_a-min_a)/(max_a-min_a)) * (max_b-min_b) + min_b;
}



//double c3d_vertex[ C3D_MAX_VERTICES, 8];
//double c3d_index[ (C3D_MAX_VERTICES-3) * 3 + 3 + 12 ]; //'After 3 vertices, every new vertex adds 3 indices

//int c3d_vi = 0;
//int c3d_index_count = 0;
//int c3d_vertex_count = 0;

int CAMERA_LENS = 0;

// 'Returns number of points in clipped triangle Or 0 if no clipping was done
int ClipTriangle(double* tri, double* uv, double* clipped_tri, double* clipped_uv)
{

	int clip_count = 0;

	double lp[3], ld[3], p1[3], p2[3], p3[3], intersect[3];

	double AB_dist, AC_dist, dist;

	//'vec(lp, 20, 30, 265)
	//'vec(ld, 20 - lp[0], 20 - lp[1], 275 - lp[2])

	int clip_dist = CAMERA_LENS-1;

	p1[0] = -1;
	p1[1] = -1;
	p1[2] = clip_dist;

	p2[0] = 1;
	p2[1] = 1;
	p2[2] = clip_dist;

	p3[0] = 1;
	p3[1] = -1;
	p3[2] = clip_dist;

	//'C3D_LinePlaneIntersection(lp, ld, p1, p2, p3, intersect)

	double pt[9];
	double pt_uv[6];

	double nc[9];
	double nc_uv[6];
	int non_clip_count = 0;

	int c_index = 0;
	int pt_uv_index = 0;
	int nc_uv_index = 0;
	int uv_index = 0;

	for(int i = 0; i <= 8; i+=3)
	{
		if( tri[i+2] >= clip_dist )
		{
			c_index = clip_count*3;
			pt[c_index] = tri[i];
			pt[c_index+1] = tri[i+1];
			pt[c_index+2] = tri[i+2];

			pt_uv_index = clip_count*2;
			uv_index = i/3*2;
			pt_uv[pt_uv_index] = uv[uv_index];
			pt_uv[pt_uv_index+1] = uv[uv_index+1];

			clip_count = clip_count + 1;
		}
		else
		{
			c_index = non_clip_count*3;
			nc[c_index] = tri[i];
			nc[c_index+1] = tri[i+1];
			nc[c_index+2] = tri[i+2];

			nc_uv_index = non_clip_count*2;
			uv_index = i/3*2;
			nc_uv[nc_uv_index] = uv[uv_index];
			nc_uv[nc_uv_index+1] = uv[uv_index+1];

			non_clip_count = non_clip_count + 1;
		}
	}

	if(clip_count == 0 || clip_count == 3 )
	{
		return 0;
	}


	switch(clip_count)
	{
		case 1:
			lp[0] = pt[0];
			lp[1] = pt[1];
			lp[2] = pt[2];

			ld[0] = nc[0] - lp[0];
			ld[1] = nc[1] - lp[1];
			ld[2] = nc[2] - lp[2];

			LinePlaneIntersection(&lp[0], &ld[0], &p1[0], &p2[0], &p3[0], &intersect[0]);

			//'dim clipped_tri[3]

			AB_dist = Distance3D(pt[0], pt[1], pt[2], nc[0], nc[1], nc[2]);
			AC_dist = Distance3D(pt[0], pt[1], pt[2], nc[3], nc[4], nc[5]);

			//'AB
			clipped_tri[0] = intersect[0];
			clipped_tri[1] = intersect[1];
			clipped_tri[2] = intersect[2];

			dist = Distance3D(pt[0], pt[1], pt[2], clipped_tri[0], clipped_tri[1], clipped_tri[2]);
			clipped_uv[0] = Interpolate(0, AB_dist, dist, pt_uv[0], nc_uv[0]);
			clipped_uv[1] = Interpolate(0, AB_dist, dist, pt_uv[1], nc_uv[1]);

			//'B
			clipped_tri[3] = nc[0];
			clipped_tri[4] = nc[1];
			clipped_tri[5] = nc[2];

			clipped_uv[2] = nc_uv[0];
			clipped_uv[3] = nc_uv[1];
			//'print "TEST: ";clipped_uv[2];", ";clipped_uv[3]

			//'C
			clipped_tri[6] = nc[3];
			clipped_tri[7] = nc[4];
			clipped_tri[8] = nc[5];

			clipped_uv[4] = nc_uv[2];
			clipped_uv[5] = nc_uv[3];

			//'print "TEST(C): (";clipped_tri[6];", ";clipped_tri[7];", ";clipped_tri[8];") (";clipped_uv[4];", ";clipped_uv[5];")"

			//'AB
			clipped_tri[9] = clipped_tri[0];
			clipped_tri[10] = clipped_tri[1];
			clipped_tri[11] = clipped_tri[2];

			clipped_uv[6] = clipped_uv[0];
			clipped_uv[7] = clipped_uv[1];

			//'C
			clipped_tri[12] = nc[3];
			clipped_tri[13] = nc[4];
			clipped_tri[14] = nc[5];

			clipped_uv[8] = nc_uv[2];
			clipped_uv[9] = nc_uv[3];

			ld[0] = nc[3] - lp[0];
			ld[1] = nc[4] - lp[1];
			ld[2] = nc[5] - lp[2];

			LinePlaneIntersection(&lp[0], &ld[0], &p1[0], &p2[0], &p3[0], &intersect[0]);

			//'AC
			clipped_tri[15] = intersect[0];
			clipped_tri[16] = intersect[1];
			clipped_tri[17] = intersect[2];

			dist = Distance3D(pt[0], pt[1], pt[2], clipped_tri[15], clipped_tri[16], clipped_tri[17]);
			clipped_uv[10] = Interpolate(0, AC_dist, dist, pt_uv[0], nc_uv[2]);
			clipped_uv[11] = Interpolate(0, AC_dist, dist, pt_uv[1], nc_uv[3]);

			return 6;

	case 2:
			//'A is the no clip
			lp[0] = pt[0];
			lp[1] = pt[1];
			lp[2] = pt[2];

			ld[0] = nc[0] - lp[0];
			ld[1] = nc[1] - lp[1];
			ld[2] = nc[2] - lp[2];

			LinePlaneIntersection(&lp[0], &ld[0], &p1[0], &p2[0], &p3[0], &intersect[0]);

			AB_dist = Distance3D(pt[0], pt[1], pt[2], nc[0], nc[1], nc[2]);
			AC_dist = Distance3D(pt[3], pt[4], pt[5], nc[0], nc[1], nc[2]);

			//'A
			clipped_tri[0] = nc[0];
			clipped_tri[1] = nc[1];
			clipped_tri[2] = nc[2];

			clipped_uv[0] = nc_uv[0];
			clipped_uv[1] = nc_uv[1];

			//'AB
			clipped_tri[3] = intersect[0];
			clipped_tri[4] = intersect[1];
			clipped_tri[5] = intersect[2];

			dist = Distance3D(nc[0], nc[1], nc[2], clipped_tri[3], clipped_tri[4], clipped_tri[5]);
			clipped_uv[2] = Interpolate(0, AB_dist, dist, nc_uv[0], pt_uv[0]);
			clipped_uv[3] = Interpolate(0, AB_dist, dist, nc_uv[1], pt_uv[1]);

			//'AC
			lp[0] = pt[3];
			lp[1] = pt[4];
			lp[2] = pt[5];

			ld[0] = nc[0] - lp[0];
			ld[1] = nc[1] - lp[1];
			ld[2] = nc[2] - lp[2];

			LinePlaneIntersection(&lp[0], &ld[0], &p1[0], &p2[0], &p3[0], &intersect[0]);

			clipped_tri[6] = intersect[0];
			clipped_tri[7] = intersect[1];
			clipped_tri[8] = intersect[2];

			dist = Distance3D(nc[0], nc[1], nc[2], clipped_tri[6], clipped_tri[7], clipped_tri[8]);
			clipped_uv[4] = Interpolate(0, AC_dist, dist, nc_uv[0], pt_uv[2]);
			clipped_uv[5] = Interpolate(0, AC_dist, dist, nc_uv[1], pt_uv[3]);


		return 3;
	}

	return 0;

}


void projectionGeometry(int cam_dist, int f_vertex_count, double* vertex3D, double* uv, double graph_offset_x, double graph_offset_y, uint32_t color,
                           double* vertex_count, double* vertex2D, double* ind_count, double* index, double* clip_dist, double* min_x, double* min_y, double* max_x, double* max_y)
{
	CAMERA_LENS = cam_dist;

	if( f_vertex_count > 4 || f_vertex_count < 3)
		return;

	int tri_index = 0;
	int uv_index = 0;

	int clip = 0;

	double clipped_tri[18], clipped_uv[12];
	double distance = 0;
	double cld = 0;
	int vi = 0;
	uint32_t r, g, b, a;
    r = ( (color >> 16) & 255);
    g = ( (color >> 8) & 255);
    b = ( color & 255);
    a = ( (color >> 24) & 255);

    //cout << "color = " << color << ", " << r << ", " << g << ", " << b << ", " << a << endl;

    int index_count = 0;
    vertex_count[0] = 0;

    int ni = 0;

	switch(f_vertex_count)
	{
        case 3:
		clip = ClipTriangle(&vertex3D[0], &uv[0], &clipped_tri[0], &clipped_uv[0]);
		if(clip > 0)
        {
            tri_index = 0;
			uv_index = 0;

			for(int i = 0; i < clip; i++)
            {
                distance = CAMERA_LENS - clipped_tri[tri_index+2];
				distance = (distance <= 0) ?  1 : distance;
				cld = (CAMERA_LENS / distance);
				ni = vi * 8;
				vertex2D[ ni + 0 ] = (cld * clipped_tri[tri_index]) + graph_offset_x;
				vertex2D[ ni + 1 ] = graph_offset_y - (cld * clipped_tri[tri_index+1]);
				vertex2D[ ni + 2 ] = r;
				vertex2D[ ni + 3 ] = g;
				vertex2D[ ni + 4 ] = b;
				vertex2D[ ni + 5 ] = a;
				vertex2D[ ni + 6 ] = clipped_uv[uv_index]; //' uv_x + (uv_w * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 0]) 'u
				vertex2D[ ni + 7 ] = clipped_uv[uv_index+1]; //'uv_y + (uv_h * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 1]) 'v

				clip_dist[0] = min(distance, clip_dist[0]);
				min_x[0] = min(vertex2D[ ni + 0], min_x[0]);
				min_y[0] = min(vertex2D[ ni + 1], min_y[0]);
				max_x[0] = max(vertex2D[ ni + 0], max_x[0]);
				max_y[0] = max(vertex2D[ ni + 1], max_y[0]);

				index[index_count] = vi;
				index_count = index_count + 1;
				vi = vi + 1;
				tri_index = tri_index + 3;
				uv_index = uv_index + 2;
            }
        }
        else
        {
			tri_index = 0;
			uv_index = 0;

			for(int i = 0; i < 3; i++)
            {
                distance = CAMERA_LENS - vertex3D[tri_index+2];
				distance = (distance<=0) ? 1 : distance;
				cld = (CAMERA_LENS / distance);
				ni = vi * 8;
				vertex2D[ ni + 0 ] = (cld * vertex3D[tri_index]) + graph_offset_x;
				vertex2D[ ni + 1 ] = graph_offset_y - (cld * vertex3D[tri_index+1]);
				vertex2D[ ni + 2 ] = r;
				vertex2D[ ni + 3 ] = g;
				vertex2D[ ni + 4 ] = b;
				vertex2D[ ni + 5 ] = a;
				vertex2D[ ni + 6 ] = uv[uv_index]; //' uv_x + (uv_w * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 0]) 'u
				vertex2D[ ni + 7 ] = uv[uv_index+1]; //'uv_y + (uv_h * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 1]) 'v

				clip_dist[0] = min(distance, clip_dist[0]);
				min_x[0] = min(vertex2D[ ni + 0], min_x[0]);
				min_y[0] = min(vertex2D[ ni + 1], min_y[0]);
				max_x[0] = max(vertex2D[ ni + 0], max_x[0]);
				max_y[0] = max(vertex2D[ ni + 1], max_y[0]);

				vi = vi + 1;
				tri_index = tri_index + 3;
				uv_index = uv_index + 2;
            }

			index[index_count] = 0;
			index[index_count+1] = 1;
			index[index_count+2] = 2;
			index_count = index_count + 3;
        }
		break;
	case 4:
		clip = ClipTriangle(&vertex3D[0], &uv[0], &clipped_tri[0], &clipped_uv[0]);
		if(clip > 0)
        {
            tri_index = 0;
			uv_index = 0;

			for(int i = 0; i < clip; i++)
            {
                distance = CAMERA_LENS - clipped_tri[tri_index+2];
				distance = (distance<=0) ? 1 : distance;
				cld = (CAMERA_LENS / distance);
				ni = vi * 8;
				vertex2D[ ni + 0 ] = (cld * clipped_tri[tri_index]) + graph_offset_x;
				vertex2D[ ni + 1 ] = graph_offset_y - (cld * clipped_tri[tri_index+1]);
				vertex2D[ ni + 2 ] = r;
				vertex2D[ ni + 3 ] = g;
				vertex2D[ ni + 4 ] = b;
				vertex2D[ ni + 5 ] = a;
				vertex2D[ ni + 6 ] = clipped_uv[uv_index]; //' uv_x + (uv_w * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 0]) 'u
				vertex2D[ ni + 7 ] = clipped_uv[uv_index+1]; //'uv_y + (uv_h * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 1]) 'v

				clip_dist[0] = min(distance, clip_dist[0]);
				min_x[0] = min(vertex2D[ ni + 0], min_x[0]);
				min_y[0] = min(vertex2D[ ni + 1], min_y[0]);
				max_x[0] = max(vertex2D[ ni + 0], max_x[0]);
				max_y[0] = max(vertex2D[ ni + 1], max_y[0]);

				index[index_count] = vi;
				index_count = index_count + 1;
				vi = vi + 1;
				tri_index = tri_index + 3;
				uv_index = uv_index + 2;
            }
        }
        else
        {
            //cout << "DBG: " << vertex3D[0] << ", " << vertex3D[1] << endl;
            tri_index = 0;
			uv_index = 0;

			for(int i = 0; i < 3; i++)
            {
                distance = CAMERA_LENS - vertex3D[tri_index+2];
				distance = (distance<=0) ? 1 : distance;
				cld = (CAMERA_LENS / distance);
				ni = vi * 8;
				vertex2D[ ni + 0 ] = (cld * vertex3D[tri_index]) + graph_offset_x;
				vertex2D[ ni + 1 ] = graph_offset_y - (cld * vertex3D[tri_index+1]);
				vertex2D[ ni + 2 ] = r;
				vertex2D[ ni + 3 ] = g;
				vertex2D[ ni + 4 ] = b;
				vertex2D[ ni + 5 ] = a;
				vertex2D[ ni + 6 ] = uv[uv_index]; //' uv_x + (uv_w * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 0]) 'u
				vertex2D[ ni + 7 ] = uv[uv_index+1]; //'uv_y + (uv_h * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 1]) 'v

				clip_dist[0] = min(distance, clip_dist[0]);
				min_x[0] = min(vertex2D[ ni + 0], min_x[0]);
				min_y[0] = min(vertex2D[ ni + 1], min_y[0]);
				max_x[0] = max(vertex2D[ ni + 0], max_x[0]);
				max_y[0] = max(vertex2D[ ni + 1], max_y[0]);

				vi = vi + 1;
				tri_index = tri_index + 3;
				uv_index = uv_index + 2;
            }

			index[index_count] = 0;
			index[index_count+1] = 1;
			index[index_count+2] = 2;
			index_count = index_count + 3;
        }

		vertex3D[3] = vertex3D[0];
		vertex3D[4] = vertex3D[1];
		vertex3D[5] = vertex3D[2];

		uv[2] = uv[0];
		uv[3] = uv[1];
		clip = ClipTriangle(&vertex3D[3], &uv[2], &clipped_tri[0], &clipped_uv[0]);

		if(clip > 0)
        {
            tri_index = 0;
			uv_index = 0;

			for(int i = 0; i < clip; i++)
            {
                distance = CAMERA_LENS - clipped_tri[tri_index+2];
				distance = (distance<=0) ? 1 : distance;
				cld = (CAMERA_LENS / distance);
				ni = vi * 8;
				vertex2D[ ni + 0 ] = (cld * clipped_tri[tri_index]) + graph_offset_x;
				vertex2D[ ni + 1 ] = graph_offset_y - (cld * clipped_tri[tri_index+1]);
				vertex2D[ ni + 2 ] = r;
				vertex2D[ ni + 3 ] = g;
				vertex2D[ ni + 4 ] = b;
				vertex2D[ ni + 5 ] = a;
				vertex2D[ ni + 6 ] = clipped_uv[uv_index]; //' uv_x + (uv_w * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 0]) 'u
				vertex2D[ ni + 7 ] = clipped_uv[uv_index+1]; //'uv_y + (uv_h * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 1]) 'v

				clip_dist[0] = min(distance, clip_dist[0]);
				min_x[0] = min(vertex2D[ ni + 0], min_x[0]);
				min_y[0] = min(vertex2D[ ni + 1], min_y[0]);
				max_x[0] = max(vertex2D[ ni + 0], max_x[0]);
				max_y[0] = max(vertex2D[ ni + 1], max_y[0]);

				index[index_count] = vi;
				index_count = index_count + 1;

				vi = vi + 1;

				tri_index = tri_index + 3;
				uv_index = uv_index + 2;
            }
        }
        else
        {
            tri_index = 3;
			uv_index = 2;

			for(int i = 0; i < 3; i++)
            {
                distance = CAMERA_LENS - vertex3D[tri_index+2];
				distance = (distance<=0) ? 1 : distance;
				cld = (CAMERA_LENS / distance);
				ni = vi * 8;
				vertex2D[ ni + 0 ] = (cld * vertex3D[tri_index]) + graph_offset_x;
				vertex2D[ ni + 1 ] = graph_offset_y - (cld * vertex3D[tri_index+1]);
				vertex2D[ ni + 2 ] = r;
				vertex2D[ ni + 3 ] = g;
				vertex2D[ ni + 4 ] = b;
				vertex2D[ ni + 5 ] = a;
				vertex2D[ ni + 6 ] = uv[uv_index]; //' uv_x + (uv_w * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 0]) 'u
				vertex2D[ ni + 7 ] = uv[uv_index+1]; //'uv_y + (uv_h * C3D_Mesh_TCoord[mesh, C3D_Mesh_Face_TCoord[mesh, face, i], 1]) 'v

				clip_dist[0] = min(distance, clip_dist[0]);
				min_x[0] = min(vertex2D[ ni + 0], min_x[0]);
				min_y[0] = min(vertex2D[ ni + 1], min_y[0]);
				max_x[0] = max(vertex2D[ ni + 0], max_x[0]);
				max_y[0] = max(vertex2D[ ni + 1], max_y[0]);

				index[index_count] = vi; //'They will already be in the right order here
				index_count = index_count + 1;
				vi = vi + 1;
				tri_index = tri_index + 3;
				uv_index = uv_index + 2;
            }

        }
        break;

	}

    vertex_count[0] = (double)vi;
    ind_count[0] = (double)index_count;

    //cout << "DEBUG: " << vertex_count[0] << ", " << ind_count[0] << endl;

}


void rc_GetProjectionGeometry(int cam_dist, uint32_t mA, int f_vertex_count, double* columns, double* uv, double graph_offset_x, double graph_offset_y, uint32_t color,
                           double* vertex_count, double* vertex2D, double* ind_count, double* index, double* clip_dist, double* min_x, double* min_y, double* max_x, double* max_y)
{
    double vertex3D[18]; // number of vertices * 3 -> ie. (x,y,z) for each vertex

    int v_index = 0;
    for(int i = 0; i < f_vertex_count; i++)
    {
		vertex3D[v_index] = MatrixValue(mA, 0, columns[i]);
		vertex3D[v_index+1] = MatrixValue(mA, 1, columns[i]);
		vertex3D[v_index+2] = MatrixValue(mA, 2, columns[i]);
		v_index += 3;
    }

    projectionGeometry(cam_dist, f_vertex_count, &vertex3D[0], uv, graph_offset_x, graph_offset_y, color,
                           vertex_count, vertex2D, ind_count, index, clip_dist, min_x, min_y, max_x, max_y);
}

// --------------------------------------------------------------------------


#endif // RC_GEOMETRY_H_INCLUDED
