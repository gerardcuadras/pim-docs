Product model data structure
============================

Product models are exported in a file with the following fields.

Attributes fields can be one of these:

- **code** (required): the product model code
- **clothing_size**: size option code for a simple select option
- **description-<locale_code>-<channel>**: localizable and scopable attribute for channel mobile one row by local_code dans channel
- **name-<locale_code>**: localizable attribute one row by local_code
- **price-<currency>**: numeric price value for this currency (example: price-EUR)
- **tshirt_style**: list of option codes for a multi select option list

Product properties fields:

- **categories**: list of category codes
- **family_variant** (required): the family variant code
- **parent**: product model code parent


.. note::

  File example:

    .. literalinclude:: examples/product_model.csv


.. note::

 To import a Product Model with variations you should import first a Product Model before importing the variations as :doc:`/import_and_export_data/product`
