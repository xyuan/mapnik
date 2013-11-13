/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2013 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_SYMBOLIZER_KEYS_HPP
#define MAPNIK_SYMBOLIZER_KEYS_HPP


namespace mapnik {

enum keys
{
    gamma = 1,
    gamma_method,
    opacity,
    alignment,
    offset,
    comp_op,
    clip,
    fill,
    fill_opacity,
    stroke,
    stroke_width,
    stroke_opacity,
    stroke_linejoin,
    stroke_linecap,
    stroke_gamma,
    stroke_gamma_method,
    stroke_dashoffset,
    stroke_dasharray,
    stroke_miterlimit,
    transform,
    rasterizer_mode,
    image_transform,
    spacing,
    max_error,
    allow_overlap,
    ignore_placement,
    width,
    height,
    file,
    filename,
    shield_dx,
    shield_dy,
    unlock_image,
    text_opacity,
    mode,
    scaling,
    filter_factor,
    mesh_size,
    premultiplied,
    smooth,
    simplify_algorithm,
    simplify_tolerance,
    halo_rasterizer,
    text_placements_
};

}


#endif // MAPNIK_SYMBOLIZER_KEYS_HPP